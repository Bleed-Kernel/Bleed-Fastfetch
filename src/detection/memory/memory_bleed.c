#include "memory.h"
#include "common/debug.h"

#include <bleed/sysinfo.h>
#include <bleed/syscalls.h>

const char* ffDetectMemory(FFMemoryResult* ram) {
    system_memory_info_t info;
    int ret = _meminfo(&info);
    if (ret != 0) {
        FF_DEBUG("_meminfo() failed: %d", ret);
        return "_meminfo() failed";
    }

    ram->bytesTotal = info.MEMORY_USABLE;
    ram->bytesUsed = info.MEMORY_USABLE - info.MEMORY_FREE;
    return nullptr;
}
