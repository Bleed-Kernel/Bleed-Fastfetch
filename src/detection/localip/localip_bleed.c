#include "localip.h"

const char* ffDetectLocalIps([[maybe_unused]] const FFLocalIpOptions* options, [[maybe_unused]] FFlist* results) {
    // Bleed has no network stack
    return "Not supported on Bleed";
}
