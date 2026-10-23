# Bleed has no dynamic loader, everything is a static ELF
include(Platform/Generic)
set(CMAKE_EXECUTABLE_SUFFIX "")
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)
set(CMAKE_DL_LIBS "")
