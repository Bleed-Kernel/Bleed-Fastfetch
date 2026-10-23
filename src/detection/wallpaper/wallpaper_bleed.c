#include "wallpaper.h"
#include "common/io.h"

const char* ffDetectWallpaper(FFstrbuf* result) {
    // Where Crime-Scene loads its wallpaper from
    const char* path = "/initrd/etc/wallpaper.png";
    if (!ffPathExists(path, FF_PATHTYPE_FILE)) {
        return "No wallpaper found";
    }
    ffStrbufSetStatic(result, path);
    return nullptr;
}
