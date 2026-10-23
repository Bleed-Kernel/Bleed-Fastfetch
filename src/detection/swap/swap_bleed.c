#include "swap.h"

const char* ffDetectSwap([[maybe_unused]] FFlist* result) {
    // Bleed has no swap, an empty list reads as disabled
    return nullptr;
}
