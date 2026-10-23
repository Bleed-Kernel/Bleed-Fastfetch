#include "libc.h"

const char* ffDetectLibc(FFLibcResult* result) {
    result->name = "blibc";
    result->version = nullptr;
    return nullptr;
}
