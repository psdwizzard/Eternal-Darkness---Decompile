#include "src/game/types.h"

/* Vorbis floor0_unpack: read floor type 0 setup from the codec header. */

typedef struct CodecSetupInfo {
    u8 pad[0x1C];
    s32 books;
} CodecSetupInfo;

typedef struct VorbisInfo {
    u8 pad[0x1C];
    CodecSetupInfo *codec_setup;
} VorbisInfo;

typedef struct Floor0Info {
    s32 order;
    s32 rate;
    s32 barkmap;
    s32 ampbits;
    s32 ampdB;
    s32 numbooks;
    s32 books[16];
    u8 pad[0x60 - 0x58];
} Floor0Info;

extern s32 oggpack_read(void *opb, s32 bits);  /* oggpack_read */
extern void *fn_8022F780(s32 size);           /* _ogg_malloc */
extern void *memset(void *data, int value, unsigned long size);

Floor0Info *floor0_unpack(VorbisInfo *vi, void *opb) {
    CodecSetupInfo *ci = vi->codec_setup;
    s32 j;
    Floor0Info *info = fn_8022F780(sizeof(Floor0Info));

    info->order = oggpack_read(opb, 8);
    info->rate = oggpack_read(opb, 16);
    info->barkmap = oggpack_read(opb, 16);
    info->ampbits = oggpack_read(opb, 6);
    info->ampdB = oggpack_read(opb, 8);
    info->numbooks = oggpack_read(opb, 4) + 1;

    if (info->order < 1) goto err_out;
    if (info->rate < 1) goto err_out;
    if (info->barkmap < 1) goto err_out;
    if (info->numbooks < 1) goto err_out;

    for (j = 0; j < info->numbooks; j++) {
        info->books[j] = oggpack_read(opb, 8);
        if (info->books[j] < 0 || info->books[j] >= ci->books) goto err_out;
    }
    return info;

err_out:
    if (info) {
        memset(info, 0, sizeof(*info));
    }
    return 0;
}
