/* GXSetScissor: encode the inclusive scissor rectangle in BP registers. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0xF8 - 4];
    u32 scissorTopLeft;
    u32 scissorBottomRight;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    do { \
        u32 *address; \
        u32 bits = *(address = &(reg)); \
        *address = (bits & ~(((1 << (size)) - 1) << (shift))) | \
                   ((val) << (shift)); \
    } while (0)

void GXSetScissor(u32 left, u32 top, u32 width, u32 height)
{
    u32 right, bottom;

    /* Bias the origin and convert the extents to inclusive endpoints. */
    right = (left += 342) + (--width);
    bottom = (top += 342) + (--height);

    SET_REG_FIELD(gx->scissorTopLeft, 11, 0, top);
    SET_REG_FIELD(gx->scissorTopLeft, 11, 12, left);
    SET_REG_FIELD(gx->scissorBottomRight, 11, 0, bottom);
    SET_REG_FIELD(gx->scissorBottomRight, 11, 12, right);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->scissorTopLeft;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->scissorBottomRight;
    gx->bpSentNot = 0;
}
