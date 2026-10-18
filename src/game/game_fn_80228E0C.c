/* __SetSURegs: copy a texture map's size and wrap bias into a texcoord's SU scale registers. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0xB8 - 4];
    u32 suTs0[8];
    u32 suTs1[8];
    u8 padF8[0x45C - 0xF8];
    u32 tImage0[8];
    u32 tMode0[8];
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 u8; u32 u32; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define GET_REG_FIELD(reg, size, shift) ((u32)((reg) >> (shift)) & ((1 << (size)) - 1))
#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))
#define GX_WRITE_RAS_REG(v) \
    do { GXWGFifo.u8 = 0x61; GXWGFifo.u32 = (u32)(v); } while (0)

void __SetSURegs(u32 tmap, u32 tcoord)
{
    u32 w, h;
    u8 s_bias, t_bias;

    w = GET_REG_FIELD(gx->tImage0[tmap], 10, 0);
    h = GET_REG_FIELD(gx->tImage0[tmap], 10, 10);
    SET_REG_FIELD(gx->suTs0[tcoord], 16, 0, w);
    SET_REG_FIELD(gx->suTs1[tcoord], 16, 0, h);
    s_bias = GET_REG_FIELD(gx->tMode0[tmap], 2, 0) == 1;
    t_bias = GET_REG_FIELD(gx->tMode0[tmap], 2, 2) == 1;
    SET_REG_FIELD(gx->suTs0[tcoord], 1, 16, s_bias);
    SET_REG_FIELD(gx->suTs1[tcoord], 1, 16, t_bias);
    GX_WRITE_RAS_REG(gx->suTs0[tcoord]);
    GX_WRITE_RAS_REG(gx->suTs1[tcoord]);
    gx->bpSentNot = 0;
}
