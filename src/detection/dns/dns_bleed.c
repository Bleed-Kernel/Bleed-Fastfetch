#include "dns.h"

const char* ffDetectDNS([[maybe_unused]] FFDNSOptions* options, [[maybe_unused]] FFlist* results) {
    // Bleed has no network stack
    return "Not supported on Bleed";
}
