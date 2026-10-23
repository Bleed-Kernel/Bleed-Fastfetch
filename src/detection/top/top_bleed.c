#include "top.h"

const char* ffTopGetProcessSnapshot([[maybe_unused]] FFlist* snapshots, [[maybe_unused]] FFTopTypes showTypes) {
    // Task cpu time is counted in uncalibrated TSC cycles, there is nothing to turn it into milliseconds with
    return "Not supported on Bleed";
}
