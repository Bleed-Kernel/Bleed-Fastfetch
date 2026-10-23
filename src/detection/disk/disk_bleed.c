#include "disk.h"
#include "common/strutil.h"

#include <bleed/sysinfo.h>
#include <bleed/syscalls.h>

const char* ffDetectDisksImpl(FFDiskOptions* options, FFlist* disks) {
    user_mount_info_t info;

    // Index 0 is the root, a tempfs in memory; every other mount is a disk under /mnt
    for (uint64_t i = 0; _mountinfo(i, &info) == 0; i++) {
        if (__builtin_expect(options->folders.length, 0)) {
            if (!ffStrbufSeparatedContainS(&options->folders, info.path, FF_DISK_FOLDER_SEPARATOR)) {
                continue;
            }
        }

        if (options->hideFolders.length && ffDiskMatchesFolderPatterns(&options->hideFolders, info.path, FF_DISK_FOLDER_SEPARATOR)) {
            continue;
        }

        if (options->hideFS.length && ffStrbufSeparatedContainS(&options->hideFS, info.fs, ':')) {
            continue;
        }

        FFDisk* disk = FF_LIST_ADD(FFDisk, *disks);
        disk->bytesTotal = info.blocks_total * info.block_size;
        disk->bytesFree = info.blocks_free * info.block_size;
        disk->filesTotal = 0;
        disk->filesUsed = 0;

        ffStrbufInitS(&disk->mountFrom, info.device);
        ffStrbufInitS(&disk->mountpoint, info.path);
        ffStrbufInitS(&disk->filesystem, info.fs);
        ffStrbufInit(&disk->name);
        disk->type = FF_DISK_VOLUME_TYPE_REGULAR_BIT;
        disk->createTime = 0;
    }

    return nullptr;
}
