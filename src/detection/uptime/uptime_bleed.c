#include "uptime.h"
#include "common/time.h"

#include <time.h>

const char* ffDetectUptime(FFUptimeResult* result) {
    // CLOCK_MONOTONIC is the HPET, which starts counting at boot
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0) {
        return "clock_gettime(CLOCK_MONOTONIC) failed";
    }

    result->uptime = (uint64_t) ts.tv_sec * 1000 + (uint64_t) ts.tv_nsec / 1000000;
    result->bootTime = ffTimeGetNow() - result->uptime;
    return nullptr;
}
