#include "cpu.h"

#include <cpuid.h>
#include <string.h>

const char* ffDetectCPUImpl([[maybe_unused]] const FFCPUOptions* options, FFCPUResult* cpu) {
    uint32_t eax = 0, ebx = 0, ecx = 0, edx = 0;
    if (!__get_cpuid(0, &eax, &ebx, &ecx, &edx)) {
        return "cpuid is not available";
    }

    char vendor[13];
    memcpy(vendor, &ebx, 4);
    memcpy(vendor + 4, &edx, 4);
    memcpy(vendor + 8, &ecx, 4);
    vendor[12] = '\0';
    ffStrbufSetS(&cpu->vendor, vendor);

    if (__get_cpuid(0x80000000, &eax, &ebx, &ecx, &edx) && eax >= 0x80000004) {
        uint32_t brand[13] = {};
        for (uint32_t i = 0; i < 3; i++) {
            __get_cpuid(0x80000002 + i, &brand[i * 4], &brand[i * 4 + 1], &brand[i * 4 + 2], &brand[i * 4 + 3]);
        }
        ffStrbufSetS(&cpu->name, (const char*) brand);
        ffStrbufTrimSpace(&cpu->name);
    }

    // The kernel only ever runs on the boot processor
    cpu->packages = 1;
    cpu->coresPhysical = 1;
    cpu->coresLogical = 1;
    cpu->coresOnline = 1;

    ffCPUDetectByCpuid(cpu);
    return nullptr;
}
