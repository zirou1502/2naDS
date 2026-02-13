#pragma once

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <CTRPluginFramework.hpp>

#include "types.h"

namespace CTRPluginFramework {

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
    // u8* GetBmpBuffer(void);

   private:
    FT_Face _face;
    std::string _file_name;
    int _font_size;
    u8* _buf;
    GlyphInfo _info;
};

}  // namespace CTRPluginFramework