BLIBC_DIR  ?= $(if $(wildcard ../blibc/include/bleed),../blibc,external/blibc)
BLIBC_REPO  = https://github.com/Bleed-Kernel/blibc.git
SYSROOT     = $(abspath $(BLIBC_DIR))/sysroot

BUILD       = build-bleed

.PHONY: all blibc clean distclean

all: bin/fastfetch

blibc:
	@if [ ! -d "$(BLIBC_DIR)" ]; then git clone $(BLIBC_REPO) $(BLIBC_DIR); fi
	@$(MAKE) -C $(BLIBC_DIR) --no-print-directory

export BLEED_SYSROOT := $(SYSROOT)

$(BUILD)/build.ninja:
	cmake -S . -B $(BUILD) -G Ninja \
		-DCMAKE_TOOLCHAIN_FILE=bleed/toolchain.cmake \
		-DBLEED_SYSROOT=$(SYSROOT) \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_FLASHFETCH=OFF \
		-DBUILD_TESTS=OFF \
		-DENABLE_THREADS=OFF \
		-DENABLE_SYSTEM_YYJSON=OFF \
		-DENABLE_EMBEDDED_PCIIDS=OFF \
		-DENABLE_EMBEDDED_AMDGPUIDS=OFF \
		-DENABLE_LTO=OFF \
		-DENABLE_IMAGE_LOGO=OFF \
		-DENABLE_ZLIB=OFF \
		-DENABLE_LUA=OFF \
		-DENABLE_LIBZFS=OFF \
		-DENABLE_WORDEXP=OFF \
		-DSET_TWEAK=OFF \
		-DINSTALL_LICENSE=OFF

bin/fastfetch: $(BUILD)/build.ninja $(SYSROOT)/lib/blibc.a FORCE
	cmake --build $(BUILD) --target fastfetch
	@mkdir -p bin
	cp $(BUILD)/fastfetch $@

FORCE:

clean:
	rm -rf $(BUILD) bin

distclean: clean
	rm -rf external
