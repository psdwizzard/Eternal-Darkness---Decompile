/* GXSetTevIndirect: configure the indirect texturing parameters of a TEV stage. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 u8; u32 u32; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))
#define GX_WRITE_RAS_REG(v) \
    do { GXWGFifo.u8 = 0x61; GXWGFifo.u32 = (u32)(v); } while (0)

void fn_80229294(u32 tev_stage, u32 ind_stage, u32 format, u32 bias_sel, u32 matrix_sel,
                 u32 wrap_s, u32 wrap_t, u8 add_prev, u8 utc_lod, u32 alpha_sel)
{
    u32 reg;

    reg = ind_stage;
    SET_REG_FIELD(reg, 2, 2, format);
    SET_REG_FIELD(reg, 3, 4, bias_sel);
    SET_REG_FIELD(reg, 2, 7, alpha_sel);
    SET_REG_FIELD(reg, 4, 9, matrix_sel);
    SET_REG_FIELD(reg, 3, 13, wrap_s);
    SET_REG_FIELD(reg, 3, 16, wrap_t);
    SET_REG_FIELD(reg, 1, 19, utc_lod);
    SET_REG_FIELD(reg, 1, 20, add_prev);
    SET_REG_FIELD(reg, 8, 24, tev_stage + 16);
    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}
