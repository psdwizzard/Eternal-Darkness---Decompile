/* GXSetChanCtrl: configure a lighting channel's control register in XF. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 pad0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef enum {
    GX_COLOR0, GX_COLOR1, GX_ALPHA0, GX_ALPHA1,
    GX_COLOR0A0, GX_COLOR1A1
} GXChannelID;

typedef enum { GX_SRC_REG, GX_SRC_VTX } GXColorSrc;
typedef enum { GX_DF_NONE, GX_DF_SIGN, GX_DF_CLAMP } GXDiffuseFn;
typedef enum { GX_AF_SPEC, GX_AF_SPOT, GX_AF_NONE } GXAttnFn;

#define GX_LIGHT0 0x01
#define GX_LIGHT1 0x02
#define GX_LIGHT2 0x04
#define GX_LIGHT3 0x08
#define GX_LIGHT4 0x10
#define GX_LIGHT5 0x20
#define GX_LIGHT6 0x40
#define GX_LIGHT7 0x80

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

typedef union GXWGPipe {
    u8 u8_data;
    u32 u32_data;
} GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8_data = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32_data = (u32)(v))

#define GX_WRITE_XF_REG(addr, val) \
    do { \
        GX_WRITE_U8(0x10); \
        GX_WRITE_U32(0x1000 + (addr)); \
        GX_WRITE_U32(val); \
    } while (0)

void GXSetChanCtrl(GXChannelID chan, u8 enable, GXColorSrc amb_src, GXColorSrc mat_src,
                 u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn)
{
    u32 reg;
    u32 idx;

    if (chan == GX_COLOR0A0) {
        idx = 0;
    } else if (chan == GX_COLOR1A1) {
        idx = 1;
    } else {
        idx = chan;
    }

    reg = 0;
    SET_REG_FIELD(reg, 1, 1, enable);
    SET_REG_FIELD(reg, 1, 0, mat_src);
    SET_REG_FIELD(reg, 1, 6, amb_src);
    SET_REG_FIELD(reg, 1, 2, (light_mask & GX_LIGHT0) != 0);
    SET_REG_FIELD(reg, 1, 3, (light_mask & GX_LIGHT1) != 0);
    SET_REG_FIELD(reg, 1, 4, (light_mask & GX_LIGHT2) != 0);
    SET_REG_FIELD(reg, 1, 5, (light_mask & GX_LIGHT3) != 0);
    SET_REG_FIELD(reg, 1, 11, (light_mask & GX_LIGHT4) != 0);
    SET_REG_FIELD(reg, 1, 12, (light_mask & GX_LIGHT5) != 0);
    SET_REG_FIELD(reg, 1, 13, (light_mask & GX_LIGHT6) != 0);
    SET_REG_FIELD(reg, 1, 14, (light_mask & GX_LIGHT7) != 0);
    SET_REG_FIELD(reg, 2, 7, (attn_fn == GX_AF_SPEC) ? GX_DF_NONE : diff_fn);
    SET_REG_FIELD(reg, 1, 9, (attn_fn != GX_AF_NONE));
    SET_REG_FIELD(reg, 1, 10, (attn_fn != GX_AF_SPEC));

    GX_WRITE_XF_REG(idx + 14, reg);
    gx->bpSentNot = 1;
    if (chan == GX_COLOR0A0) {
        GX_WRITE_XF_REG(16, reg);
    } else if (chan == GX_COLOR1A1) {
        GX_WRITE_XF_REG(17, reg);
    }
}
