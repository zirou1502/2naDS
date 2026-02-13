#include "cheats.hpp"

#include "Memory/MemManager.hpp"
#include "Render/Font.hpp"

#include FT_FREETYPE_H

namespace CTRPluginFramework {

bool DrawOSD(const Screen& scr) {
    if (!scr.IsTop) return false;
    Font font("Leipzig2.ttf");
    font.SetFontSize(50);
    int pos_x = 100;
    int pos_y = 120;

    std::string str = "Hello World";

    for (char ch : str) {
        font.LoadChar(ch);
        Font::GlyphInfo info = font.GetGlyphInfo();

        for (int i = 0; i < info.rows; i++)
            for (int j = 0; j < info.width; j++) {
                u8 c = info.buf[i * info.pitch + j];
                scr.DrawPixel(pos_x + j + info.left, pos_y - info.top + i, (c > 0 ? Color::White : Color::Black));
            }

        pos_x += info.width;
    }
    return true;
}

void test(MenuEntry* entry) {
    OSD::Run(DrawOSD);
    return;
}

}  // namespace CTRPluginFramework