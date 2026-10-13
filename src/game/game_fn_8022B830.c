/* GXSetViewportJitter: record the viewport in the GX state and load the
 * XF viewport scale/offset registers, offsetting by half a line for the
 * odd field. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct GXData {
    u8 pad0[0x2];
    u16 bpSent;
    u8 pad4[0x43C - 0x4];
    f32 vpLeft;
    f32 vpTop;
    f32 vpWd;
    f32 vpHt;
    f32 vpNearz;
    f32 vpFarz;
    u8 fgRange;
    u8 pad455[3];
    f32 fgSideX;
} GXData;
extern GXData *gx;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    f32 f32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8 = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = (u32)(v))
#define GX_WRITE_F32(v) (GXWGFifo.f32 = (f32)(v))

extern void __GXSetRange(f32 nearz, f32 fgSideX);

void fn_8022B830(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field)
{
    f32 sx, sy, sz, ox, oy, oz;
    f32 zmin, zmax;

    if (field == 0) {
        top -= 0.5f;
    }
    sx = wd / 2.0f;
    sy = -ht / 2.0f;
    ox = 342.0f + (left + wd / 2.0f);
    oy = ht / 2.0f;
    oy = 342.0f + (top + oy);
    zmin = 16777215.0f * nearz;
    zmax = 16777215.0f * farz;
    sz = zmax - zmin;
    oz = zmax;

    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = wd;
    gx->vpHt = ht;
    gx->vpNearz = nearz;
    gx->vpFarz = farz;

    if (gx->fgRange) {
        __GXSetRange(nearz, gx->fgSideX);
    }

    GX_WRITE_U8(0x10);
    GX_WRITE_U32(0x5101A);
    GX_WRITE_F32(sx);
    GX_WRITE_F32(sy);
    GX_WRITE_F32(sz);
    GX_WRITE_F32(ox);
    GX_WRITE_F32(oy);
    GX_WRITE_F32(oz);
    gx->bpSent = 1;
}
