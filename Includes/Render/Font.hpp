#pragma once

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <CTRPluginFramework.hpp>

#include "types.h"

namespace CTRPluginFramework {

extern "C" {
extern const u8 Leipzig2_ttf[];
extern const int Leipzig2_ttf_size;
}

class Font {
   public:
    typedef struct GlyphInfo {
        u8* buf;
        int width;
        int rows;
        int left;
        int top;
        int pitch;
    } GlyphInfo;
    Font(const std::string& file_name);
    ~Font();
    bool SetFontSize(int size);
    int GetFontSize(void);
    bool LoadChar(const u32& c);
    GlyphInfo GetGlyphInfo(void);

   private:
    FT_Face _face;
    int _font_size;
    GlyphInfo _info;
};

}  // namespace CTRPluginFramework