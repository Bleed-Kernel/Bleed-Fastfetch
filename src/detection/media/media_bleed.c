#include "media.h"

void ffDetectMediaImpl(FFMediaResult* media, [[maybe_unused]] bool saveCover) {
    ffStrbufAppendS(&media->error, "Not supported on Bleed");
}
