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

void GXSetCopyFilter(u8 aa, u8 sample_pattern[12][2], u8 vf, u8 vfilter[7])
{
    u32 samples[4];
    u32 filter0;
    u32 filter1;

    if (aa != 0) {
        samples[0] = 0;
        SET_REG_FIELD(samples[0], 4, 0, sample_pattern[0][0]);
        SET_REG_FIELD(samples[0], 4, 4, sample_pattern[0][1]);
        SET_REG_FIELD(samples[0], 4, 8, sample_pattern[1][0]);
        SET_REG_FIELD(samples[0], 4, 12, sample_pattern[1][1]);
        SET_REG_FIELD(samples[0], 4, 16, sample_pattern[2][0]);
        SET_REG_FIELD(samples[0], 4, 20, sample_pattern[2][1]);
        SET_REG_FIELD(samples[0], 8, 24, 1);

        samples[1] = 0;
        SET_REG_FIELD(samples[1], 4, 0, sample_pattern[3][0]);
        SET_REG_FIELD(samples[1], 4, 4, sample_pattern[3][1]);
        SET_REG_FIELD(samples[1], 4, 8, sample_pattern[4][0]);
        SET_REG_FIELD(samples[1], 4, 12, sample_pattern[4][1]);
        SET_REG_FIELD(samples[1], 4, 16, sample_pattern[5][0]);
        SET_REG_FIELD(samples[1], 4, 20, sample_pattern[5][1]);
        SET_REG_FIELD(samples[1], 8, 24, 2);

        samples[2] = 0;
        SET_REG_FIELD(samples[2], 4, 0, sample_pattern[6][0]);
        SET_REG_FIELD(samples[2], 4, 4, sample_pattern[6][1]);
        SET_REG_FIELD(samples[2], 4, 8, sample_pattern[7][0]);
        SET_REG_FIELD(samples[2], 4, 12, sample_pattern[7][1]);
        SET_REG_FIELD(samples[2], 4, 16, sample_pattern[8][0]);
        SET_REG_FIELD(samples[2], 4, 20, sample_pattern[8][1]);
        SET_REG_FIELD(samples[2], 8, 24, 3);

        samples[3] = 0;
        SET_REG_FIELD(samples[3], 4, 0, sample_pattern[9][0]);
        SET_REG_FIELD(samples[3], 4, 4, sample_pattern[9][1]);
        SET_REG_FIELD(samples[3], 4, 8, sample_pattern[10][0]);
        SET_REG_FIELD(samples[3], 4, 12, sample_pattern[10][1]);
        SET_REG_FIELD(samples[3], 4, 16, sample_pattern[11][0]);
        SET_REG_FIELD(samples[3], 4, 20, sample_pattern[11][1]);
        SET_REG_FIELD(samples[3], 8, 24, 4);
    } else {
        samples[0] = 0x01666666;
        samples[1] = 0x02666666;
        samples[2] = 0x03666666;
        samples[3] = 0x04666666;
    }
    GX_WRITE_RAS_REG(samples[0]);
    GX_WRITE_RAS_REG(samples[1]);
    GX_WRITE_RAS_REG(samples[2]);
    GX_WRITE_RAS_REG(samples[3]);

    filter0 = 0;
    filter1 = 0;
    SET_REG_FIELD(filter0, 8, 24, 0x53);
    SET_REG_FIELD(filter1, 8, 24, 0x54);
    if (vf != 0) {
        SET_REG_FIELD(filter0, 6, 0, vfilter[0]);
        SET_REG_FIELD(filter0, 6, 6, vfilter[1]);
        SET_REG_FIELD(filter0, 6, 12, vfilter[2]);
        SET_REG_FIELD(filter0, 6, 18, vfilter[3]);

        SET_REG_FIELD(filter1, 6, 0, vfilter[4]);
        SET_REG_FIELD(filter1, 6, 6, vfilter[5]);
        SET_REG_FIELD(filter1, 6, 12, vfilter[6]);
    } else {
        filter0 = 0x53595000;
        filter1 = 0x54000015;
    }
    GX_WRITE_RAS_REG(filter0);
    GX_WRITE_RAS_REG(filter1);

    gx->bpSentNot = 0;
}
