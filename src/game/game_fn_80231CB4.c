/* Unpack a Vorbis floor1 setup header (floor1_info_unpack). */
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

typedef struct CodecSetup {
    u8 pad[0x1C];
    s32 books;
} CodecSetup;

typedef struct VorbisInfo {
    u8 pad[0x1C];
    CodecSetup *codec_setup;
} VorbisInfo;

extern void *fn_8022F780(s32 size);
extern s32 fn_8022E868(void *, s32);

FloorInfo *fn_80231CB4(VorbisInfo *vi, void *opb)
{
    CodecSetup *ci = vi->codec_setup;
    int j, k, count = 0, maxclass = -1, rangebits;
    FloorInfo *info = fn_8022F780(sizeof(FloorInfo));

    info->partitions = fn_8022E868(opb, 5);
    for (j = 0; j < info->partitions; j++) {
        info->partitionclass[j] = fn_8022E868(opb, 4);
        if (maxclass < info->partitionclass[j]) maxclass = info->partitionclass[j];
    }

    for (j = 0; j < maxclass + 1; j++) {
        info->class_dim[j] = fn_8022E868(opb, 3) + 1;
        info->class_subs[j] = fn_8022E868(opb, 2);
        if (info->class_subs[j]) info->class_book[j] = fn_8022E868(opb, 8);
        if (info->class_book[j] >= ci->books) goto err_out;
        for (k = 0; k < (1 << info->class_subs[j]); k++) {
            info->class_subbook[j][k] = fn_8022E868(opb, 8) - 1;
            if (info->class_subbook[j][k] < -1 || info->class_subbook[j][k] >= ci->books)
                goto err_out;
        }
    }

    info->mult = fn_8022E868(opb, 2) + 1;
    rangebits = fn_8022E868(opb, 4);

    for (j = 0, k = 0; j < info->partitions; j++) {
        count += info->class_dim[info->partitionclass[j]];
        for (; k < count; k++) {
            int t = info->postlist[k + 2] = fn_8022E868(opb, rangebits);
            if (t < 0 || t >= (1 << rangebits)) goto err_out;
        }
    }
    info->postlist[0] = 0;
    info->postlist[1] = 1 << rangebits;
    return info;

err_out:
    return 0;
}
