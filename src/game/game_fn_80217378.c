typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct VIPosition {
    u16 dispPosX, dispPosY;
    u16 dispSizeX, dispSizeY;
    u16 adjustedDispPosX, adjustedDispPosY;
    u16 adjustedDispSizeY, adjustedPanPosY, adjustedPanSizeY;
    u16 fbSizeX, fbSizeY;
    u16 panPosX, panPosY, panSizeX, panSizeY;
    u16 padding;
    s32 xfbMode;
    u32 nonInter, tv;
    u8 wordPerLine, std, wpl;
    u8 padding1F;
    u32 bufAddr, tfbb, bfbb;
    u8 xof;
    u8 reserved2D[3];
    s32 black;
    s32 threeD;
    u32 rbufAddr, rtfbb, rbfbb;
    void *timing;
} VIPosition;

extern u16 lbl_80641AC8[];
/* 64-bit "changed" register mask (one bit per VI register, MSB = reg 0).
 * symbols.txt splits its low word out as lbl_8064DA8C. */
extern volatile u64 changed;

#define VI_BITMASK(index) (1ull << (63 - (index)))
#define MARK_CHANGED(index) (changed |= VI_BITMASK(index))
#define ToPhysical(addr) ((u32)(addr) & 0x3FFFFFFF)
#define IS_LOWER_16MB(addr) ((addr) < 0x1000000)

static inline void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine, s32 xfbMode,
                            u16 dispPosY, u32 *tfbb, u32 *bfbb) {
    u32 bytesPerLine, xoffInWords;
    u32 tmp;

    xoffInWords = (u32)panPosX / 16;
    bytesPerLine = (u32)wordPerLine * 32;

    *tfbb = bufAddr + xoffInWords * 32 + bytesPerLine * panPosY;
    *bfbb = (xfbMode == 0) ? *tfbb : (*tfbb + bytesPerLine);

    if (dispPosY % 2 == 1) {
        tmp = *tfbb;
        *tfbb = *bfbb;
        *bfbb = tmp;
    }

    *tfbb = ToPhysical(*tfbb);
    *bfbb = ToPhysical(*bfbb);
}

void setFbbRegs(VIPosition *hv, u32 *tfbb, u32 *bfbb, u32 *rtfbb, u32 *rbfbb) {
    u16 *regs = lbl_80641AC8;
    u32 shifted;

    calcFbbs(hv->bufAddr, hv->panPosX, hv->adjustedPanPosY, hv->wordPerLine, hv->xfbMode,
             hv->adjustedDispPosY, tfbb, bfbb);

    if (hv->threeD) {
        calcFbbs(hv->rbufAddr, hv->panPosX, hv->adjustedPanPosY, hv->wordPerLine, hv->xfbMode,
                 hv->adjustedDispPosY, rtfbb, rbfbb);
    }

    if (IS_LOWER_16MB(*tfbb) && IS_LOWER_16MB(*bfbb) && IS_LOWER_16MB(*rtfbb) &&
        IS_LOWER_16MB(*rbfbb)) {
        shifted = 0;
    } else {
        shifted = 1;
    }

    if (shifted) {
        *tfbb >>= 5;
        *bfbb >>= 5;
        *rtfbb >>= 5;
        *rbfbb >>= 5;
    }

    regs[0xF] = *tfbb;
    MARK_CHANGED(0xF);
    regs[0xE] = (shifted << 12) | ((*tfbb >> 16) | (hv->xof << 8));
    MARK_CHANGED(0xE);
    regs[0x13] = *bfbb;
    MARK_CHANGED(0x13);
    regs[0x12] = *bfbb >> 16;
    MARK_CHANGED(0x12);

    if (hv->threeD) {
        regs[0x11] = *rtfbb;
        MARK_CHANGED(0x11);
        regs[0x10] = *rtfbb >> 16;
        MARK_CHANGED(0x10);
        regs[0x15] = *rbfbb;
        MARK_CHANGED(0x15);
        regs[0x14] = *rbfbb >> 16;
        MARK_CHANGED(0x14);
    }
}
