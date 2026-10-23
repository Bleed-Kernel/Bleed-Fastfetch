#include "displayserver.h"
#include "common/io.h"
#include "common/bleed/tasks.h"

#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <bleed/display.h>

static bool findDesktop(const user_task_info_t* info, void* userdata) {
    if (strcmp(info->name, "crime-scene") != 0) {
        return true;
    }
    *(bool*) userdata = true;
    return false;
}

void ffConnectDisplayServerImpl(FFDisplayServerResult* ds) {
    // Crime-Scene is Bleed's desktop, it is the window manager and the desktop in one program
    bool desktop = false;
    ffBleedForEachTask(findDesktop, &desktop);
    if (desktop) {
        ffStrbufSetStatic(&ds->wmProcessName, "crime-scene");
        ffStrbufSetStatic(&ds->wmPrettyName, "Crime-Scene");
        ffStrbufSetStatic(&ds->deProcessName, "crime-scene");
        ffStrbufSetStatic(&ds->dePrettyName, "Crime-Scene");
    }

    // There is one screen, the framebuffer the bootloader set up
    FF_AUTO_CLOSE_FD int fd = open("/dev/fb0", O_RDONLY);
    if (fd < 0) {
        return;
    }

    struct fb_info info = {};
    if (ioctl(fd, FB_IOC_GET_INFO, &info) != 0 || info.width == 0 || info.height == 0) {
        return;
    }

    ffdsAppendDisplay(ds,
        (uint32_t) info.width,
        (uint32_t) info.height,
        0,
        0,
        0,
        0,
        0,
        0,
        nullptr,
        FF_DISPLAY_TYPE_UNKNOWN,
        true,
        0,
        0,
        0,
        "/dev/fb0");
}
