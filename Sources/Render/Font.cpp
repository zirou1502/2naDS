#include "Render/Font.hpp"

#include "Extra.hpp"

namespace CTRPluginFramework {

Font::Font(const std::string& file_name) : _file_name(file_name), _buf(nullptr), _face(nullptr) {
    int res;
    FT_Library library;
    char path[256];
    std::string tid;
    library = GetFTLibrary();
    Process::GetTitleID(tid);
    sprintf(path, "/luma/plugins/%s/fonts/%s", tid.c_str(), file_name.c_str());
    res = File::Exists(path);
    if (res == 0) {
        MessageBox("File doesn't exist")();
        return;
    }

    File file(path, File::READ);
    if (!file.IsOpen()) {
        MessageBox("Could not open file")();
        return;
    }

    u32 size = file.GetSize();
    if (size == 0) {
        MessageBox("File size is 0")();
        return;
    }

    _buf = (u8*)calloc(sizeof(u8), size);
    if (_buf == nullptr) {
        MessageBox("Could not alloc memory")();
    }

    file.Read(_buf, size);
    res = FT_New_Memory_Face(library, _buf, size, 0, &_face);
    if (res != 0) {
        MessageBox("Could not open font")();
        return;
    }
}

Font::~Font() {
    if (_face != nullptr) {
        FT_Done_Face(_face);
        _face = nullptr;
    }
    if (_buf != nullptr) {
        free(_buf);
        _buf = nullptr;
    }
}

bool Font::SetFontSize(int size) {
    if (_buf == nullptr) return false;
    if (_face == nullptr) return false;
    int res;
    _font_size = size;
    res = FT_Set_Pixel_Sizes(_face, 0, _font_size);
    if (res != 0) {
        MessageBox("Could set font size")();
        return false;
    }
    return true;
}

int Font::GetFontSize(void) { return _font_size; }

bool Font::LoadChar(const u32& c) {
    if (_buf == nullptr) return false;
    if (_face == nullptr) return false;
    int res;
    res = FT_Load_Char(_face, c, FT_LOAD_RENDER);
    if (res != 0) {
        MessageBox("Could not load char")();
        return false;
    }
    return true;
}

Font::GlyphInfo Font::GetGlyphInfo(void) {
    FT_GlyphSlot slot = _face->glyph;
    _info.buf = slot->bitmap.buffer;
    _info.width = slot->bitmap.width;
    _info.rows = slot->bitmap.rows;
    _info.left = slot->bitmap_left;
    _info.top = slot->bitmap_top;
    _info.pitch = slot->bitmap.pitch;
    return _info;
}


}  // namespace CTRPluginFramework