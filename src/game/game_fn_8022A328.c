/* GXSetFog: compute the fog A/B/C coefficients from the screen-space
 * start/end and the projection near/far planes, then load the fog
 * registers (0xEE-0xF2) through the BP command stream. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int s32;
typedef float f32;

typedef struct GXData {
    u8 pad0[0x2];
    u16 bpSentNot;     /* 0x002 */
} GXData;
extern GXData *gx;

typedef int GXFogType;
typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;
volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

#define GX_WRITE_RAS_REG(val) \
    do { \
        GXWGFifo.u8 = 0x61; \
        GXWGFifo.u32 = (val); \
    } while (0)

void GXSetFog(GXFogType type, GXColor *color, f32 startz, f32 endz, f32 nearz, f32 farz)
{
    u32 fogclr, fog0, fog1, fog2, fog3;
    f32 A, B, B_mant, C, a, c;
    s32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;

    if (farz == nearz || endz == startz) {
        A = 0.0f;
        B = 0.5f;
        C = 0.0f;
    } else {
        A = (farz * nearz) / ((farz - nearz) * (endz - startz));
        B = farz / (farz - nearz);
        C = startz / (endz - startz);
    }

    B_mant = B;
    B_expn = 0;
    while (B_mant > 1.0) {
        B_mant *= 0.5f;
        B_expn++;
    }
    while (B_mant > 0.0f && B_mant < 0.5) {
        B_mant *= 2.0f;
        B_expn--;
    }

    a = A / (f32)(1 << (B_expn + 1));
    b_m = 8.388638e6f * B_mant;
    b_s = B_expn + 1;
    c = C;

    fog1 = 0;
    SET_REG_FIELD(fog1, 24, 0, b_m);
    SET_REG_FIELD(fog1, 8, 24, 0xEF);

    fog2 = 0;
    SET_REG_FIELD(fog2, 24, 0, b_s);
    SET_REG_FIELD(fog2, 8, 24, 0xF0);

    a_hex = *(u32 *)&a;
    c_hex = *(u32 *)&c;

    fog0 = 0;
    SET_REG_FIELD(fog0, 11, 0, (a_hex >> 12) & 0x7FF);
    SET_REG_FIELD(fog0, 8, 11, (a_hex >> 23) & 0xFF);
    SET_REG_FIELD(fog0, 1, 19, (a_hex >> 31));
    SET_REG_FIELD(fog0, 8, 24, 0xEE);

    fog3 = 0;
    SET_REG_FIELD(fog3, 11, 0, (c_hex >> 12) & 0x7FF);
    SET_REG_FIELD(fog3, 8, 11, (c_hex >> 23) & 0xFF);
    SET_REG_FIELD(fog3, 1, 19, (c_hex >> 31));
    SET_REG_FIELD(fog3, 3, 21, type);
    SET_REG_FIELD(fog3, 8, 24, 0xF1);

    fogclr = 0;
    SET_REG_FIELD(fogclr, 8, 0, color->b);
    SET_REG_FIELD(fogclr, 8, 8, color->g);
    SET_REG_FIELD(fogclr, 8, 16, color->r);
    SET_REG_FIELD(fogclr, 8, 24, 0xF2);

    GX_WRITE_RAS_REG(fog0);
    GX_WRITE_RAS_REG(fog1);
    GX_WRITE_RAS_REG(fog2);
    GX_WRITE_RAS_REG(fog3);
    GX_WRITE_RAS_REG(fogclr);

    gx->bpSentNot = 0;
}
