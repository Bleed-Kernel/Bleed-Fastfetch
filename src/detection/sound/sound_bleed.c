#include "sound.h"
#include "common/io.h"

const char* ffDetectSound([[maybe_unused]] FFSoundOptions* options, FFlist* devices) {
    // The only audio driver is AC'97, it shows up as /dev/audio0
    if (!ffPathExists("/dev/audio0", FF_PATHTYPE_ANY)) {
        return nullptr;
    }

    FFSoundDevice* device = FF_LIST_ADD(FFSoundDevice, *devices);
    ffStrbufInitStatic(&device->identifier, "/dev/audio0");
    ffStrbufInitStatic(&device->name, "AC'97 Audio");
    ffStrbufInitStatic(&device->platformApi, "/dev/audio0");
    device->volume = FF_SOUND_VOLUME_UNKNOWN;
    device->type = (FFSoundType) (FF_SOUND_TYPE_MAIN | FF_SOUND_TYPE_ACTIVE);
    return nullptr;
}
