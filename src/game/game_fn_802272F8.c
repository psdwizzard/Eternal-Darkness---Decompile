/* GXSetCopyFilter: program the EFB copy anti-aliasing sample pattern and the
 * vertical (deflicker) filter coefficients. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
} GXData;

extern GXData *gx;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8 = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = (u32)(v))
#define GX_WRITE_RAS_REG(v) \
    do {                    \
        GX_WRITE_U8(0x61);  \
        GX_WRITE_U32(v);    \
    } while (0)

void fn_802272F8(u8 aa, u8 sample_pattern[12][2], u8 vf, u8 vfilter[7])
{
    u32 msk;
    u32 coeff0;
    u32 coeff1;
    u32 coeff2;
    u32 coeff3;

    if (aa != 0) {
        coeff0 = 0;
        SET_REG_FIELD(coeff0, 4, 0, sample_pattern[0][0]);
        SET_REG_FIELD(coeff0, 4, 4, sample_pattern[0][1]);
        SET_REG_FIELD(coeff0, 4, 8, sample_pattern[1][0]);
        SET_REG_FIELD(coeff0, 4, 12, sample_pattern[1][1]);
        SET_REG_FIELD(coeff0, 4, 16, sample_pattern[2][0]);
        SET_REG_FIELD(coeff0, 4, 20, sample_pattern[2][1]);
        SET_REG_FIELD(coeff0, 8, 24, 1);

        coeff1 = 0;
        SET_REG_FIELD(coeff1, 4, 0, sample_pattern[3][0]);
        SET_REG_FIELD(coeff1, 4, 4, sample_pattern[3][1]);
        SET_REG_FIELD(coeff1, 4, 8, sample_pattern[4][0]);
        SET_REG_FIELD(coeff1, 4, 12, sample_pattern[4][1]);
        SET_REG_FIELD(coeff1, 4, 16, sample_pattern[5][0]);
        SET_REG_FIELD(coeff1, 4, 20, sample_pattern[5][1]);
        SET_REG_FIELD(coeff1, 8, 24, 2);

        coeff2 = 0;
        SET_REG_FIELD(coeff2, 4, 0, sample_pattern[6][0]);
        SET_REG_FIELD(coeff2, 4, 4, sample_pattern[6][1]);
        SET_REG_FIELD(coeff2, 4, 8, sample_pattern[7][0]);
        SET_REG_FIELD(coeff2, 4, 12, sample_pattern[7][1]);
        SET_REG_FIELD(coeff2, 4, 16, sample_pattern[8][0]);
        SET_REG_FIELD(coeff2, 4, 20, sample_pattern[8][1]);
        SET_REG_FIELD(coeff2, 8, 24, 3);

        coeff3 = 0;
        SET_REG_FIELD(coeff3, 4, 0, sample_pattern[9][0]);
        SET_REG_FIELD(coeff3, 4, 4, sample_pattern[9][1]);
        SET_REG_FIELD(coeff3, 4, 8, sample_pattern[10][0]);
        SET_REG_FIELD(coeff3, 4, 12, sample_pattern[10][1]);
        SET_REG_FIELD(coeff3, 4, 16, sample_pattern[11][0]);
        SET_REG_FIELD(coeff3, 4, 20, sample_pattern[11][1]);
        SET_REG_FIELD(coeff3, 8, 24, 4);
    } else {
        coeff0 = 0x01666666;
        coeff1 = 0x02666666;
        coeff2 = 0x03666666;
        coeff3 = 0x04666666;
    }
    GX_WRITE_RAS_REG(coeff0);
    GX_WRITE_RAS_REG(coeff1);
    GX_WRITE_RAS_REG(coeff2);
    GX_WRITE_RAS_REG(coeff3);

    if (vf != 0) {
        coeff0 = 0;
        SET_REG_FIELD(coeff0, 6, 0, vfilter[0]);
        SET_REG_FIELD(coeff0, 8, 24, 0x53);
        SET_REG_FIELD(coeff0, 6, 6, vfilter[1]);
        SET_REG_FIELD(coeff0, 6, 12, vfilter[2]);
        SET_REG_FIELD(coeff0, 6, 18, vfilter[3]);

        coeff1 = 0;
        SET_REG_FIELD(coeff1, 6, 0, vfilter[4]);
        SET_REG_FIELD(coeff1, 8, 24, 0x54);
        SET_REG_FIELD(coeff1, 6, 6, vfilter[5]);
        SET_REG_FIELD(coeff1, 6, 12, vfilter[6]);
    } else {
        coeff0 = 0x53595000;
        coeff1 = 0x54000015;
    }
    GX_WRITE_RAS_REG(coeff0);
    GX_WRITE_RAS_REG(coeff1);

    gx->bpSentNot = 0;
}
