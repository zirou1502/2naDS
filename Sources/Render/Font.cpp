#include "Render/Font.hpp"

#include "Extra.hpp"
#include "Render/Fonts/Leipzig.h"

namespace CTRPluginFramework {

Font::Font(const std::string& file_name) : _face(nullptr) {
    int res;
    FT_Library library;
    library = GetFTLibrary();
    res = FT_New_Memory_Face(library, Leipzig, Leipzig_size, 0, &_face);
    if (res != 0) {
        MessageBox("Could not open font")();
        return;
    }
}

Font::~Font() {
    if (_face == nullptr) return;
    FT_Done_Face(_face);
    _face = nullptr;
}

bool Font::SetFontSize(int size) {
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
