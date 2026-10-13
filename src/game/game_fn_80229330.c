/* Set an indirect texture matrix (GXSetIndTexMtx). */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;
extern const float lbl_80651700;

typedef union GXWGPipe { u8 u8; u32 u32; float f32; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8 = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = (u32)(v))
#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | (((u32)(value) << (shift)) & (((1UL << (width)) - 1) << (shift))))

void fn_80229330(int matrixId, const float matrix[2][3], s8 scale)
{
    u32 index;
    u32 reg;
    s32 coefficients[2][3];

    switch (matrixId) {
    case 1: case 2: case 3:
        index = matrixId - 1;
        break;
    case 5: case 6: case 7:
        index = matrixId - 5;
        break;
    case 9: case 10: case 11:
        index = matrixId - 9;
        break;
    default:
        index = 0;
        break;
    }
    /* Bias the shared exponent and pack two 11-bit coefficients per column. */
    scale += 17;
    coefficients[0][0] = (s32)(lbl_80651700 * matrix[0][0]);
    coefficients[1][0] = (s32)(lbl_80651700 * matrix[1][0]);
    reg = (u32)coefficients[0][0] & 0x7FF;
    SET_FIELD(reg, 11, 11, coefficients[1][0]);
    SET_FIELD(reg, 2, 22, scale);
    SET_FIELD(reg, 8, 24, index * 3 + 6);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(reg);

    coefficients[0][1] = (s32)(lbl_80651700 * matrix[0][1]);
    coefficients[1][1] = (s32)(lbl_80651700 * matrix[1][1]);
    reg = (u32)coefficients[0][1] & 0x7FF;
    SET_FIELD(reg, 11, 11, coefficients[1][1]);
    SET_FIELD(reg, 2, 22, (u32)scale >> 2);
    SET_FIELD(reg, 8, 24, index * 3 + 7);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(reg);

    coefficients[0][2] = (s32)(lbl_80651700 * matrix[0][2]);
    coefficients[1][2] = (s32)(lbl_80651700 * matrix[1][2]);
    reg = (u32)coefficients[0][2] & 0x7FF;
    SET_FIELD(reg, 11, 11, coefficients[1][2]);
    SET_FIELD(reg, 2, 22, (u32)scale >> 4);
    SET_FIELD(reg, 8, 24, index * 3 + 8);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(reg);
    gx->bpSentNot = 0;
}
