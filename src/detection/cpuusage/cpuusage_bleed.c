#include "fastfetch.h"
#include "detection/cpuusage/cpuusage.h"
#include "common/bleed/tasks.h"

typedef struct UsageData {
    uint64_t inUse;
    uint64_t total;
} UsageData;

static bool addUsage(const user_task_info_t* info, void* userdata) {
    UsageData* data = userdata;
    user_task_usage_t usage;
    if (_taskusage(info->id, &usage) != 0) {
        return true;
    }

    // Kernel tasks spin when there is nothing else to run, their time is the idle time
    data->total += usage.cpu_time;
    if (info->privilege_level == PRIVILEGE_USER) {
        data->inUse += usage.cpu_time;
    }
    return true;
}

const char* ffGetCpuUsageInfo(FFlist* cpuTimes) {
    UsageData data = {};
    ffBleedForEachTask(addUsage, &data);
    if (data.total == 0) {
        return "_taskusage() reported no cpu time";
    }

    FFCpuUsageInfo* info = FF_LIST_ADD(FFCpuUsageInfo, *cpuTimes);
    info->inUseAll = data.inUse;
    info->totalAll = data.total;
    return nullptr;
}
