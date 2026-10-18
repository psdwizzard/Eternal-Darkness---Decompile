/* GXGetProjectionv: return the cached projection type and matrix terms. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef float f32;

typedef struct {
    u8 pad[0x420];
    u32 projType;
    f32 projMtx[6];
} GXData;

extern GXData *gx;

void GXGetProjectionv(f32 *projection) {
    projection[0] = (f32)gx->projType;
    projection[1] = gx->projMtx[0];
    projection[2] = gx->projMtx[1];
    projection[3] = gx->projMtx[2];
    projection[4] = gx->projMtx[3];
    projection[5] = gx->projMtx[4];
    projection[6] = gx->projMtx[5];
}
