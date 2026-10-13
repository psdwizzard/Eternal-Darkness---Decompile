/* __GXSetTmemConfig (0x80229054): Dolphin SDK GXInit.c.
 * Programs the 8 TMEM even/odd region pairs (SETIMAGE1/2 for each texmap)
 * for either the large-cache layout (config 1) or the default layout. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_U8(v) (GXWGFifo.u8 = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = (u32)(v))

#define GX_WRITE_RAS_REG(v) \
    do { \
        GX_WRITE_U8(0x61); \
        GX_WRITE_U32(v); \
    } while (0)

void __GXSetTmemConfig(u32 config) {
    switch (config) {
    case 1:
        GX_WRITE_RAS_REG(0x8C0D8000);
        GX_WRITE_RAS_REG(0x900DC000);
        GX_WRITE_RAS_REG(0x8D0D8800);
        GX_WRITE_RAS_REG(0x910DC800);
        GX_WRITE_RAS_REG(0x8E0D9000);
        GX_WRITE_RAS_REG(0x920DD000);
        GX_WRITE_RAS_REG(0x8F0D9800);
        GX_WRITE_RAS_REG(0x930DD800);
        GX_WRITE_RAS_REG(0xAC0DA000);
        GX_WRITE_RAS_REG(0xB00DE000);
        GX_WRITE_RAS_REG(0xAD0DA800);
        GX_WRITE_RAS_REG(0xB10DE800);
        GX_WRITE_RAS_REG(0xAE0DB000);
        GX_WRITE_RAS_REG(0xB20DF000);
        GX_WRITE_RAS_REG(0xAF0DB800);
        GX_WRITE_RAS_REG(0xB30DF800);
        break;
    case 0:
    default:
        GX_WRITE_RAS_REG(0x8C0D8000);
        GX_WRITE_RAS_REG(0x900DC000);
        GX_WRITE_RAS_REG(0x8D0D8400);
        GX_WRITE_RAS_REG(0x910DC400);
        GX_WRITE_RAS_REG(0x8E0D8800);
        GX_WRITE_RAS_REG(0x920DC800);
        GX_WRITE_RAS_REG(0x8F0D8C00);
        GX_WRITE_RAS_REG(0x930DCC00);
        GX_WRITE_RAS_REG(0xAC0D9000);
        GX_WRITE_RAS_REG(0xB00DD000);
        GX_WRITE_RAS_REG(0xAD0D9400);
        GX_WRITE_RAS_REG(0xB10DD400);
        GX_WRITE_RAS_REG(0xAE0D9800);
        GX_WRITE_RAS_REG(0xB20DD800);
        GX_WRITE_RAS_REG(0xAF0D9C00);
        GX_WRITE_RAS_REG(0xB30DDC00);
        break;
    }
}
