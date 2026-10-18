typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1EC];
    u32 cpDisp;
    u8 pad1F0[0x1FC - 0x1F0];
    u32 cpTex;
} GXData;

extern GXData *gx;

/* GXSetCopyClamp: select which EFB edges clamp during display and texture copies. */
void GXSetCopyClamp(int mode)
{
    u8 top = (mode & 1) == 1;
    u8 bottom = (mode & 2) == 2;

    gx->cpDisp = (gx->cpDisp & ~1) | (u32)top;
    gx->cpDisp = (gx->cpDisp & ~2) | ((u32)bottom << 1);
    gx->cpTex = (gx->cpTex & ~1) | (u32)top;
    gx->cpTex = (gx->cpTex & ~2) | ((u32)bottom << 1);
}
