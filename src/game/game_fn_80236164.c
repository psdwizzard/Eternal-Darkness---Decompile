/* vorbis_synthesis: Vorbis vorbis_synthesis. */

#include "src/game/types.h"

typedef struct VorbisModeParam {
    s32 blockflag;  /* 0x00 */
    s32 windowtype; /* 0x04 */
    s32 transformtype; /* 0x08 */
    s32 mapping;    /* 0x0C */
} VorbisModeParam;

typedef struct CodecSetupInfo {
    s32 blocksizes[2];                /* 0x00 */
    u8 pad08[0x20 - 0x08];
    VorbisModeParam *mode_param[64];  /* 0x20 */
    s32 map_type[64];                 /* 0x120 */
} CodecSetupInfo;

typedef struct VorbisInfo {
    s32 version;                  /* 0x00 */
    s32 channels;                 /* 0x04 */
    u8 pad08[0x1C - 0x08];
    CodecSetupInfo *codec_setup;  /* 0x1C */
} VorbisInfo;

typedef struct BackendLookup {
    u8 pad00[0x14];
    s32 modebits;  /* 0x14 */
    void **mode;   /* 0x18 */
} BackendLookup;

typedef struct VorbisDspState {
    VorbisInfo *vi;  /* 0x00 */
    u8 pad04[0x48 - 0x04];
    BackendLookup *backend_state; /* 0x48 */
} VorbisDspState;

typedef struct VorbisBlock {
    float **pcm;         /* 0x00 */
    u8 opb[0x18 - 0x04]; /* 0x04 */
    s32 lW;              /* 0x18 */
    s32 W;               /* 0x1C */
    s32 nW;              /* 0x20 */
    s32 pcmend;          /* 0x24 */
    s32 mode;            /* 0x28 */
    s32 eofflag;         /* 0x2C */
    s32 granulepos;      /* 0x30 */
    s32 sequence;        /* 0x34 */
    VorbisDspState *vd;  /* 0x38 */
} VorbisBlock;

typedef struct OggPacket {
    u8 *packet;     /* 0x00 */
    s32 bytes;      /* 0x04 */
    s32 b_o_s;      /* 0x08 */
    s32 e_o_s;      /* 0x0C */
    s32 granulepos; /* 0x10 */
    s32 packetno;   /* 0x14 */
} OggPacket;

typedef struct MappingFuncs {
    u8 pad00[0x1C];
    s32 (*inverse)(VorbisBlock *, void *); /* 0x1C */
} MappingFuncs;

extern MappingFuncs *_mapping_P[];

extern void fn_8022F890(VorbisDspState *vd);
extern void _vorbis_block_ripcord(VorbisBlock *vb);
extern void oggpack_readinit(void *opb, u8 *buf, s32 bytes);
extern s32 oggpack_read(void *opb, s32 bits);
extern void *fn_8022F8C4(s32 size);

s32 vorbis_synthesis(VorbisBlock *vb, OggPacket *op) {
    VorbisDspState *vd = vb->vd;
    VorbisInfo *vi = vd->vi;
    BackendLookup *b = vd->backend_state;
    CodecSetupInfo *ci = vi->codec_setup;
    void *opb = vb->opb;
    s32 type, mode, i;

    fn_8022F890(vd);
    _vorbis_block_ripcord(vb);
    oggpack_readinit(opb, op->packet, op->bytes);

    if (oggpack_read(opb, 1) != 0) {
        return -135;
    }

    mode = oggpack_read(opb, b->modebits);
    if (mode == -1) {
        return -136;
    }

    vb->mode = mode;
    vb->W = ci->mode_param[mode]->blockflag;
    if (vb->W) {
        vb->lW = oggpack_read(opb, 1);
        vb->nW = oggpack_read(opb, 1);
        if (vb->nW == -1) {
            return -136;
        }
    } else {
        vb->lW = 0;
        vb->nW = 0;
    }

    vb->granulepos = op->granulepos;
    vb->sequence = op->packetno - 3;
    vb->eofflag = op->e_o_s;

    vb->pcmend = ci->blocksizes[vb->W];
    vb->pcm = fn_8022F8C4(sizeof(*vb->pcm) * vi->channels);
    for (i = 0; i < vi->channels; i++) {
        vb->pcm[i] = fn_8022F8C4(vb->pcmend * sizeof(*vb->pcm[i]));
    }

    type = ci->map_type[ci->mode_param[mode]->mapping];
    return _mapping_P[type]->inverse(vb, b->mode[mode]);
}
