typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1EC];
    u32 cpDisp;
    u8 pad1F0[0x1FC - 0x1F0];
    u32 cpTex;
} GXData;

extern GXData *gx;

/* GXSetDispCopyFrame2Field: configure the display copy's field mode. */
void fn_80227114(int mode)
{
    gx->cpDisp = (gx->cpDisp & ~0x3000) | ((u32)mode << 12);
    gx->cpTex = gx->cpTex & ~0x3000;
}
