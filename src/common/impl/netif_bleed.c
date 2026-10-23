#include "common/netif.h"

// Bleed has no network stack

bool ffNetifGetDefaultRouteImplV4([[maybe_unused]] FFNetifDefaultRouteResult* result) {
    return false;
}

bool ffNetifGetDefaultRouteImplV6([[maybe_unused]] FFNetifDefaultRouteResult* result) {
    return false;
}
