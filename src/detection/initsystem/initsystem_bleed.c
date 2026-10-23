#include "initsystem.h"

const char* ffDetectInitSystem([[maybe_unused]] FFInitSystemResult* result) {
    // The kernel starts the desktop (or the shell) itself, there is no init
    return "Bleed has no init system";
}
