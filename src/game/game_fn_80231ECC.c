/* Allocate a copy of a Vorbis floor1 setup. */
#include "src/game/types.h"

typedef struct FloorInfo {
    s32 partitions;
    u8 partitionclass[31];
    u8 class_dim[16];
    u8 class_subs[16];
    u8 class_book[16];
    s8 class_subbook[16][8];
    s32 mult;
    s32 postlist[75];
} FloorInfo;

extern void *fn_8022F780(int size);
extern void *memcpy(void *, const void *, unsigned long);

FloorInfo *floor1_copy_info(const FloorInfo *source)
{
    FloorInfo *copy = fn_8022F780(sizeof(FloorInfo));
    return memcpy(copy, source, sizeof(FloorInfo));
}
