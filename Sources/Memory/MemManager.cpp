#include "Memory/MemManager.hpp"

#include "3ds.h"
#include "csvc.h"

namespace CTRPluginFramework {

Result MemManager::Alloc(u32 size) {
    Result res;
    res = svcControlMemoryUnsafe(_addr, 0, size, MEMOP_ALLOC, MEMPERM_READWRITE);
    if (R_SUCCEEDED(res)) {
        _size = size;
    }
    return res;
}

Result MemManager::Free(void) {
    Result res;
    res = svcControlMemoryUnsafe(_addr, *_addr, _size, MEMOP_FREE, MEMPERM_DONTCARE);
    *_addr = 0;
    _size = 0;
    return res;
}

}  // namespace CTRPluginFramework