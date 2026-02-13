#include "Extra.hpp"

#include "types.h"

namespace CTRPluginFramework {

FT_Library library;
bool is_inited = false;

void PatchProcessFont(void) {
    int res;
    res = FT_Init_FreeType(&library);
    is_inited = (res ? false : true);
    return;
}

void OnProcessExitFont(void) { FT_Done_FreeType(library); }

FT_Library GetFTLibrary(void) { return library; }

}  // namespace CTRPluginFramework