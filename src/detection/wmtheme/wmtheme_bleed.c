#include "wmtheme.h"

bool ffDetectWmTheme(FFstrbuf* themeOrError) {
    ffStrbufAppendS(themeOrError, "Not supported on Bleed");
    return false;
}
