#include "terminalfont.h"
#include "detection/terminalshell/terminalshell.h"

bool ffDetectTerminalFontPlatform([[maybe_unused]] const FFTerminalResult* terminal, FFTerminalFontResult* terminalFont) {
    // Bleed's terminals draw with the PSF font built into the kernel and Crime-Scene, neither says which
    ffStrbufAppendS(&terminalFont->error, "Not supported on Bleed");
    return false;
}
