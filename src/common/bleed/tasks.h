#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <bleed/scheduler.h>
#include <bleed/syscalls.h>

// Bleed has no /proc. Tasks are looked up by pid one at a time, the same way its task manager does,
// and the scan stops once it has seen as many as the kernel says exist.
#define FF_BLEED_PID_SCAN 4096

static inline bool ffBleedTaskAlive(const user_task_info_t* info) {
    return info->state != TASK_FREE && info->state != TASK_DEAD && info->state != TASK_ZOMBIE;
}

// Calls `cb` for every live task until it returns false
static inline void ffBleedForEachTask(bool (*cb)(const user_task_info_t* info, void* userdata), void* userdata) {
    uint64_t want = _taskcount();
    uint64_t seen = 0;

    for (uint64_t pid = 0; pid < FF_BLEED_PID_SCAN && seen < want; pid++) {
        user_task_info_t info;
        if (_taskinfo(pid, &info) != 0) {
            continue;
        }
        seen++;

        if (ffBleedTaskAlive(&info) && !cb(&info, userdata)) {
            return;
        }
    }
}
