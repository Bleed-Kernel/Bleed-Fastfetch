# cross build for Bleed (https://github.com/Bleed-Kernel), statically linked against blibc
set(CMAKE_SYSTEM_NAME Bleed)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

if(NOT BLEED_SYSROOT)
    set(BLEED_SYSROOT "$ENV{BLEED_SYSROOT}")
endif()
if(NOT BLEED_SYSROOT)
    message(FATAL_ERROR "BLEED_SYSROOT has to point at blibc's sysroot")
endif()
# try_compile projects get a fresh cache, this carries the sysroot into them
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES BLEED_SYSROOT)

set(CMAKE_C_COMPILER x86_64-elf-gcc)
set(CMAKE_AR x86_64-elf-ar)
set(CMAKE_RANLIB x86_64-elf-ranlib)

# blibc's headers come first, gcc's own (cpuid.h, stdatomic.h and friends) fill in after them
execute_process(COMMAND ${CMAKE_C_COMPILER} -print-file-name=include OUTPUT_VARIABLE BLEED_GCC_INCLUDE OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_C_FLAGS_INIT "-D__bleed__=1 -ffreestanding -fno-pic -fno-stack-protector -nostdinc -isystem ${BLEED_SYSROOT}/include -idirafter ${BLEED_GCC_INCLUDE}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static -nostdlib -no-pie ${BLEED_SYSROOT}/lib/start.o")
set(CMAKE_C_STANDARD_LIBRARIES "${BLEED_SYSROOT}/lib/blibc.a -lgcc")

# only ever look in blibc, never at the host's libraries
set(CMAKE_FIND_ROOT_PATH "${BLEED_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(PKG_CONFIG_EXECUTABLE "" CACHE FILEPATH "no pkg-config for Bleed" FORCE)
