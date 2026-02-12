#pragma once
#include <CTRPluginFramework.hpp>

#include "types.h"

namespace CTRPluginFramework {

class MemManager {
   private:
    u32 _size;
    u32 _addr;

   public:
    MemManager() : _addr(0), _size(0) {};
    ~MemManager() {};
    Result Alloc(u32 size);
    Result Free();
    void* GetPtr() { return &_addr; };
    u32 GetSize() { return _size; };
};

}  // namespace CTRPluginFramework