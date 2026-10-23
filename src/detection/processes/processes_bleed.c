#include "processes.h"
#include "common/bleed/tasks.h"

typedef struct CountData {
    bool countKprocs;
    uint32_t count;
} CountData;

static bool countTask(const user_task_info_t* info, void* userdata) {
    CountData* data = userdata;
    if (data->countKprocs || info->privilege_level == PRIVILEGE_USER) {
        data->count++;
    }
    return true;
}

const char* ffDetectProcesses(const FFProcessesOptions* options, FFProcessesResult* result) {
    CountData data = { .countKprocs = options->countKprocs };
    ffBleedForEachTask(countTask, &data);

    // Every Bleed task is single threaded
    result->processes = data.count;
    result->threads = data.count;
    return nullptr;
}
