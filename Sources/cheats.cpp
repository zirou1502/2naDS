#include "cheats.hpp"

#include <freetype2/ft2build.h>

#include "Memory/MemManager.hpp"
#include FT_FREETYPE_H

namespace CTRPluginFramework {

void test(MenuEntry* entry) {
    int res = 0;
    FT_Library library;
    FT_Face face;
    char path[256];
    std::string tid;
    u8* buf;

    res = FT_Init_FreeType(&library);
    if (res != 0) {
        MessageBox("Ft_Init failed")();
        return;
    }

    Process::GetTitleID(tid);
    sprintf(path, "/luma/plugins/%s/fonts/tom-thumb.otf", tid.c_str());
    res = File::Exists(path);
    if (res == 0) {
        MessageBox("File doesn't exist")();
    }

    File file(path, File::READ);
    if (!file.IsOpen()) {
        MessageBox("File open failed")();
        FT_Done_FreeType(library);
        return;
    }

    u32 size = file.GetSize();
    if (size == 0) {
        MessageBox("File size is 0")();
        FT_Done_FreeType(library);
        return;
    }

    buf = (u8*)calloc(sizeof(u8), size);
    if (buf == nullptr) {
        MessageBox("Could not alloc memory")();
    }

    file.Read(buf, size);
    res = FT_New_Memory_Face(library, buf, size, 0, &face);
    if (res != 0) {
        MessageBox("Could not open font")();
        free(buf);
        FT_Done_FreeType(library);
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 20);
    res = FT_Load_Char(face, 'A', FT_LOAD_RENDER);
    if (res != 0) {
        MessageBox("Could not load char")();
        free(buf);
        FT_Done_Face(face);
        FT_Done_FreeType(library);
        return;
    }

    FT_GlyphSlot slot = face->glyph;
    FT_Bitmap& bmp = slot->bitmap;

    const Screen& scr = OSD::GetTopScreen();
    int pos_x = 100;
    int pos_y = 120;

    for (int i = 0; i < bmp.rows; i++) {
        for (int j = 0; j < bmp.width; j++) {
            unsigned char c = bmp.buffer[i * bmp.pitch + j];
            if (c > 0) {
                scr.DrawPixel(pos_x + j + slot->bitmap_left, pos_y + i + slot->bitmap_top, Color::White);
            }
        }
    }

    OSD::SwapBuffers();
    Sleep(Seconds(5));

    free(buf);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return;
}

}  // namespace CTRPluginFramework
