#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>

#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework {

using StringVector = std::vector<std::string>;

typedef enum {
    Priv = 1,
    User = 2,
    PrivUser = Priv | User,
} WatchMode;

typedef enum {
    Read = 1,
    Write = 2,
    ReadWrite = Read | Write,
} WatchOP;

typedef enum {
    Byte = 1,    // 0000
    HalfW = 3,   // 0011
    Word = 0xF,  // 1111
} WatchSize;

typedef struct {
    u32 far;
    u32 lr;
    u32 pc;
} WatchpointInfo;

void Watchpoint(MenuEntry* entry);

}  // namespace CTRPluginFramework
#endif
