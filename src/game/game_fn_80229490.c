/* Set the scale of an indirect texture stage (GXSetIndTexCoordScale). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 reserved0[0x2];
    u16 bpSentNot;
    u8 reserved4[0x128 - 0x4];
    u32 IndTexScale0;
    u32 IndTexScale1;
} GXData;

extern GXData *gx;

#define GX_WRITE_U8(v) (*(volatile u8 *)0xCC008000 = (u8)(v))
#define GX_WRITE_U32(v) (*(volatile u32 *)0xCC008000 = (u32)(v))

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetIndTexCoordScale(int indStage, int scaleS, int scaleT)
{
    switch (indStage) {
    case 0:
        SET_FIELD(gx->IndTexScale0, 4, 0, scaleS);
        SET_FIELD(gx->IndTexScale0, 4, 4, scaleT);
        SET_FIELD(gx->IndTexScale0, 8, 24, 0x25);
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->IndTexScale0);
        break;
    case 1:
        SET_FIELD(gx->IndTexScale0, 4, 8, scaleS);
        SET_FIELD(gx->IndTexScale0, 4, 12, scaleT);
        SET_FIELD(gx->IndTexScale0, 8, 24, 0x25);
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->IndTexScale0);
        break;
    case 2:
        SET_FIELD(gx->IndTexScale1, 4, 0, scaleS);
        SET_FIELD(gx->IndTexScale1, 4, 4, scaleT);
        SET_FIELD(gx->IndTexScale1, 8, 24, 0x26);
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->IndTexScale1);
        break;
    case 3:
        SET_FIELD(gx->IndTexScale1, 4, 8, scaleS);
        SET_FIELD(gx->IndTexScale1, 4, 12, scaleT);
        SET_FIELD(gx->IndTexScale1, 8, 24, 0x26);
        GX_WRITE_U8(0x61);
        GX_WRITE_U32(gx->IndTexScale1);
        break;
    }
    gx->bpSentNot = 0;
}
