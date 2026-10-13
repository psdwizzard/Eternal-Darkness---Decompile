/* fn_8022B4B8: GXSetProjection (Dolphin SDK GXTransform.c).
 * Caches the projection type and the six relevant matrix terms in the GX
 * state, then sends them to XF register 0x1020 through the FIFO. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;
typedef f32 Mtx44[4][4];

typedef enum {
    GX_PERSPECTIVE,
    GX_ORTHOGRAPHIC
} GXProjectionType;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    f32 f32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad1[0x41C];
    u32 projType;
    f32 projMtx[6];
} GXData;

extern GXData *gx;

static inline void __GXSetProjection(void) {
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = 0x61020;
    GXWGFifo.f32 = gx->projMtx[0];
    GXWGFifo.f32 = gx->projMtx[1];
    GXWGFifo.f32 = gx->projMtx[2];
    GXWGFifo.f32 = gx->projMtx[3];
    GXWGFifo.f32 = gx->projMtx[4];
    GXWGFifo.f32 = gx->projMtx[5];
    GXWGFifo.u32 = gx->projType;
}

void fn_8022B4B8(Mtx44 mtx, GXProjectionType type) {
    gx->projType = type;
    gx->projMtx[0] = mtx[0][0];
    gx->projMtx[2] = mtx[1][1];
    gx->projMtx[4] = mtx[2][2];
    gx->projMtx[5] = mtx[2][3];
    if (type == GX_ORTHOGRAPHIC) {
        gx->projMtx[1] = mtx[0][3];
        gx->projMtx[3] = mtx[1][3];
    } else {
        gx->projMtx[1] = mtx[0][2];
        gx->projMtx[3] = mtx[1][2];
    }
    __GXSetProjection();
    gx->bpSentNot = 1;
}
