typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x1EC];
    u32 cpTex;
} GXData;

extern GXData *gx;

/* GXSetCopyGamma: select the gamma correction for EFB copies. */
void fn_80227520(int gamma)
{
    gx->cpTex = (gx->cpTex & ~0x180UL) | ((u32)gamma << 7);
}
