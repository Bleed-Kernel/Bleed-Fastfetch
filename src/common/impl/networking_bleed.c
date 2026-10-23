#include "common/networking.h"

// Bleed has no network stack

const char* ffNetworkingSendHttpRequest([[maybe_unused]] FFNetworkingState* state, [[maybe_unused]] const char* host, [[maybe_unused]] uint16_t port, [[maybe_unused]] const char* path, [[maybe_unused]] const char* headers) {
    return "Not supported on Bleed";
}

const char* ffNetworkingRecvHttpResponse([[maybe_unused]] FFNetworkingState* state, [[maybe_unused]] FFstrbuf* buffer) {
    return "Not supported on Bleed";
}
