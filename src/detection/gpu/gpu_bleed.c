#include "gpu.h"

const char* ffDetectGPUImpl([[maybe_unused]] const FFGPUOptions* options, [[maybe_unused]] FFlist* gpus) {
    // PCI devices are not visible from userspace yet
    return "Not supported on Bleed";
}
