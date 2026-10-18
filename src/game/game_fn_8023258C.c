#include "src/game/types.h"

typedef struct CodecSetup {
    s32 blockSizes[2];
} CodecSetup;

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

extern s32 oggpack_read(void *stream, s32 bits);
extern void vorbis_info_clear(CodecInfo *info);
extern void __assertion_failed(void *, void *, void *);
extern char lbl_806517EC;
extern char lbl_806517F0;

s32 _vorbis_unpack_info(CodecInfo *info, void *stream)
{
    CodecSetup *setup = info->setup;

    if (setup == 0) {
        __assertion_failed(&lbl_806517EC, &lbl_806517F0, (void *)0xAA);
        return -0x81;
    }

    info->version = oggpack_read(stream, 32);
    if (info->version != 0) {
        return -0x86;
    }
    info->channels = oggpack_read(stream, 8);
    info->rate = oggpack_read(stream, 32);
    info->bitrateUpper = oggpack_read(stream, 32);
    info->bitrateNominal = oggpack_read(stream, 32);
    info->bitrateLower = oggpack_read(stream, 32);
    setup->blockSizes[0] = 1ULL << oggpack_read(stream, 4);
    setup->blockSizes[1] = 1 << oggpack_read(stream, 4);

    if (info->rate >= 1 && info->channels >= 1 &&
        setup->blockSizes[0] >= 8 &&
        setup->blockSizes[1] >= setup->blockSizes[0] &&
        oggpack_read(stream, 1) == 1) {
        return 0;
    }

    __assertion_failed(&lbl_806517EC, &lbl_806517F0, (void *)0xC5);
    vorbis_info_clear(info);
    return -0x85;
}
