/* fn_802276AC: GXCopyDisp (Dolphin SDK GXFrameBuf.c).
 * Copies the EFB to the external frame buffer at dest, optionally clearing
 * the EFB, temporarily forcing the PE control/z-mode registers as needed. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))
#define GET_REG_FIELD(reg, size, shift) (((u32)(reg) >> (shift)) & ((1 << (size)) - 1))

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define GX_WRITE_RAS_REG(val) \
    do { \
        GXWGFifo.u8 = 0x61; \
        GXWGFifo.u32 = (val); \
    } while (0)

typedef struct GXData {
    u8 pad0[0x2];
    u16 bpSentNot;       /* 0x002 */
    u8 pad4[0x1D0 - 0x4];
    u32 cmode0;          /* 0x1D0 */
    u32 cmode1;          /* 0x1D4 */
    u32 zmode;           /* 0x1D8 */
    u32 peCtrl;          /* 0x1DC */
    u8 pad1E0[0x1F0 - 0x1E0];
    u32 cpDispSrc;       /* 0x1F0 */
    u32 cpDispSize;      /* 0x1F4 */
    u32 cpDispStride;    /* 0x1F8 */
    u32 cpDisp;          /* 0x1FC */
    u8 aa;               /* 0x200 */
} GXData;

extern GXData *gx;

void fn_802276AC(void *dest, u8 clear) {
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8 changePeCtrl;

    if (clear) {
        reg = gx->zmode;
        SET_REG_FIELD(reg, 1, 0, 1);
        SET_REG_FIELD(reg, 3, 1, 7);
        GX_WRITE_RAS_REG(reg);
        reg = gx->cmode0;
        SET_REG_FIELD(reg, 1, 0, 0);
        SET_REG_FIELD(reg, 1, 1, 0);
        GX_WRITE_RAS_REG(reg);
    }

    changePeCtrl = 0;
    tempPeCtrl = gx->peCtrl;
    if (gx->aa && GET_REG_FIELD(tempPeCtrl, 3, 0) != 3) {
        SET_REG_FIELD(tempPeCtrl, 3, 0, 3);
        changePeCtrl = 1;
    }
    if ((clear || GET_REG_FIELD(tempPeCtrl, 3, 0) == 3) && GET_REG_FIELD(tempPeCtrl, 1, 6) == 1) {
        changePeCtrl = 1;
        SET_REG_FIELD(tempPeCtrl, 1, 6, 0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(tempPeCtrl);
    }

    GX_WRITE_RAS_REG(gx->cpDispSrc);
    GX_WRITE_RAS_REG(gx->cpDispSize);
    GX_WRITE_RAS_REG(gx->cpDispStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    SET_REG_FIELD(reg, 24, 0, phyAddr >> 5);
    SET_REG_FIELD(reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG(reg);

    SET_REG_FIELD(gx->cpDisp, 1, 11, clear);
    SET_REG_FIELD(gx->cpDisp, 1, 14, 0);
    SET_REG_FIELD(gx->cpDisp, 8, 24, 0x52);
    GX_WRITE_RAS_REG(gx->cpDisp);

    if (clear) {
        GX_WRITE_RAS_REG(gx->zmode);
        GX_WRITE_RAS_REG(gx->cmode0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(gx->peCtrl);
    }
    gx->bpSentNot = 0;
}
