#include "os.h"
#include "common/io.h"

void ffDetectOSImpl(FFOSResult* os) {
    ffStrbufSetStatic(&os->name, "Bleed");
    ffStrbufSetStatic(&os->prettyName, "Bleed");
    ffStrbufSetStatic(&os->id, "bleed");

    // Written by the kernel build: r<commit count>-g<hash>[-dirty]
    if (ffReadFileBuffer("/initrd/proc/version", &os->version)) {
        ffStrbufTrimRightSpace(&os->version);
    }
}
