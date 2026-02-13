#pragma once

#include <freetype2/ft2build.h>

#include "types.h"

#include FT_FREETYPE_H

namespace CTRPluginFramework {

extern FT_Library library;
extern bool is_inited;

void PatchProcessFont(void);
void OnProcessExitFont(void);
FT_Library GetFTLibrary(void);

}  // namespace CTRPluginFramework
