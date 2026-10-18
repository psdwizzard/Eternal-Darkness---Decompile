#include "src/game/types.h"

typedef struct CodecSetup CodecSetup;

typedef struct CodecInfo {
    s32 version;
    s32 channels;
    s32 rate;
    s32 bitrateUpper;
    s32 bitrateNominal;
    s32 bitrateLower;
    s32 bitrateWindow;
    CodecSetup *setup;
} CodecInfo;

extern void *memset(void *dest, int value, unsigned long size);
extern void *fn_8022F780(int size);

/* Initialize the stream information and allocate its codec setup. */
void vorbis_info_init(CodecInfo *info)
{
    memset(info, 0, sizeof(*info));
    info->setup = fn_8022F780(0xDD4);
}
