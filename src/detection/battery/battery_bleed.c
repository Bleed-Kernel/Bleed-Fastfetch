#include "battery.h"
#include "common/io.h"

#include <stdio.h>
#include <string.h>

const char* ffDetectBattery([[maybe_unused]] FFBatteryOptions* options, FFlist* results) {
    // One line of text, e.g. "battery: 81% discharging (3120/3850 mAh, 11420 mV)" or "battery: none"
    FF_STRBUF_AUTO_DESTROY content = ffStrbufCreate();
    if (!ffReadFileBuffer("/dev/power", &content)) {
        return "Failed to read /dev/power";
    }

    unsigned percent = 0;
    char state[16] = "";
    if (sscanf(content.chars, "battery: %u%% %15s", &percent, state) != 2) {
        return nullptr; // No battery
    }

    FFBatteryResult* battery = FF_LIST_ADD(FFBatteryResult, *results);
    ffStrbufInit(&battery->manufacturer);
    ffStrbufInit(&battery->manufactureDate);
    ffStrbufInit(&battery->modelName);
    ffStrbufInit(&battery->technology);
    ffStrbufInit(&battery->serial);
    battery->capacity = percent;
    battery->temperature = FF_BATTERY_TEMP_UNSET;
    battery->cycleCount = 0;
    battery->timeRemaining = -1;

    if (strcmp(state, "charging") == 0) {
        battery->status = FF_BATTERY_STATUS_CHARGING | FF_BATTERY_STATUS_AC_CONNECTED;
    } else if (strcmp(state, "full") == 0) {
        battery->status = FF_BATTERY_STATUS_AC_CONNECTED;
    } else if (strcmp(state, "discharging") == 0) {
        battery->status = FF_BATTERY_STATUS_DISCHARGING;
    } else {
        battery->status = FF_BATTERY_STATUS_UNKNOWN;
    }

    return nullptr;
}
