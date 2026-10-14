/* GXClearVtxDesc: clear vertex descriptors, retaining direct positions. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 reserved0[0x14];
    u32 vcdLo;
    u32 vcdHi;
    u8 reserved1C[0x41C - 0x1C];
    u8 hasNrms;
    u8 hasBiNrms;
    u8 reserved41E[0x4F4 - 0x41E];
    u32 dirtyState;
} GXData;

extern GXData *gx;

void fn_802254D0(void)
{
    gx->vcdLo = 0;
    gx->vcdLo = (gx->vcdLo & ~(3UL << 9)) | (1UL << 9);
    gx->vcdHi = 0;
    gx->hasNrms = 0;
    gx->hasBiNrms = 0;
    gx->dirtyState |= 8;
}
