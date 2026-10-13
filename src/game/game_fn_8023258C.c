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

extern s32 fn_8022E868(void *stream, s32 bits);
extern void fn_802326F8(CodecInfo *info);
extern void fn_800F8BAC(void *, void *, void *);
extern char lbl_806517EC;
extern char lbl_806517F0;

s32 fn_8023258C(CodecInfo *info, void *stream)
{
    CodecSetup *setup = info->setup;

    if (setup == 0) {
        fn_800F8BAC(&lbl_806517EC, &lbl_806517F0, (void *)0xAA);
        return -0x81;
    }

    info->version = fn_8022E868(stream, 32);
    if (info->version != 0) {
        return -0x86;
    }
    info->channels = fn_8022E868(stream, 8);
    info->rate = fn_8022E868(stream, 32);
    info->bitrateUpper = fn_8022E868(stream, 32);
    info->bitrateNominal = fn_8022E868(stream, 32);
    info->bitrateLower = fn_8022E868(stream, 32);
    setup->blockSizes[0] = 1ULL << fn_8022E868(stream, 4);
    setup->blockSizes[1] = 1 << fn_8022E868(stream, 4);

    if (info->rate >= 1 && info->channels >= 1 &&
        setup->blockSizes[0] >= 8 &&
        setup->blockSizes[1] >= setup->blockSizes[0] &&
        fn_8022E868(stream, 1) == 1) {
        return 0;
    }

    fn_800F8BAC(&lbl_806517EC, &lbl_806517F0, (void *)0xC5);
    fn_802326F8(info);
    return -0x85;
}
