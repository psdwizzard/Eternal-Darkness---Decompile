typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef struct GXData {
    u8 pad0[2];
    u16 vLim;
    u8 pad4[0x14 - 4];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad1C[0x41C - 0x1C];
    u8 hasNrms;
    u8 hasBiNrms;
} GXData;

extern GXData *gx;

typedef union { u8 byte; u32 word; } GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;

void fn_80224908(void)
{
    GXData *g = gx;
    u32 lo = g->vcdLo;
    s32 lo13, lo15, normal;
    u32 hi;
    s32 hi14, hi12, hi10, hi8, hi6, hi4, hi2, hi0;
    s32 vertexLimit, count;

    lo13 = ((lo >> 13) & 3) ? 1 : 0;
    lo15 = ((lo >> 15) & 3) ? 1 : 0;
    vertexLimit = lo13 + lo15;

    normal = g->hasBiNrms != 0 ? 2 : (g->hasNrms != 0 ? 1 : 0);

    hi = g->vcdHi;
    hi0 = (hi & 3) ? 1 : 0;
    hi2 = ((hi >> 2) & 3) ? 1 : 0;
    count = hi0 + hi2;
    hi4 = ((hi >> 4) & 3) ? 1 : 0;
    count += hi4;
    hi6 = ((hi >> 6) & 3) ? 1 : 0;
    count += hi6;
    hi8 = ((hi >> 8) & 3) ? 1 : 0;
    count += hi8;
    hi10 = ((hi >> 10) & 3) ? 1 : 0;
    count += hi10;
    hi12 = ((hi >> 12) & 3) ? 1 : 0;
    count += hi12;
    hi14 = ((hi >> 14) & 3) ? 1 : 0;
    count += hi14;

    GXWGFifo.byte = 0x10;
    GXWGFifo.word = 0x1008;
    GXWGFifo.word = (count << 4) | (vertexLimit | (normal << 2));
    gx->vLim = 1;
}
