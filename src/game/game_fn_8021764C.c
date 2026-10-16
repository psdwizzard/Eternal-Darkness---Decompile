typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef int BOOL;

extern u16 lbl_80641AC8[];
extern volatile u32 lbl_8064DA88, lbl_8064DA8C;
/* These registers occupy the high half of the 64-bit changed-register mask.
 * Read and preserve the low half when updating the mask. */
#define MARK_CHANGED(index) do { \
    changedHigh = lbl_8064DA88; \
    changedLow = lbl_8064DA8C; \
    updatedHigh = changedHigh; \
    updatedHigh |= (0x80000000u >> (index)); \
    lbl_8064DA8C = changedLow; \
    lbl_8064DA88 = (u32)updatedHigh; \
} while (0)

/* VI setVerticalRegs */
void fn_8021764C(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven,
                 u16 psbOdd, u16 psbEven, BOOL black) {
    u32 changedLow;
    u32 changedHigh;
    u64 updatedHigh;
    u16 *regs = lbl_80641AC8;
    u16 actualPrbOdd, actualPrbEven, actualPsbOdd, actualPsbEven;
    u16 actualAcv;
    u16 c, d;

    if (equ >= 10) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }

    if (dispPosY % 2 == 0) {
        actualPrbOdd = (u16)(prbOdd + d * dispPosY);
        actualPsbOdd = (u16)(psbOdd + d * ((c * acv - dispSizeY) - dispPosY));
        actualPrbEven = (u16)(prbEven + d * dispPosY);
        actualPsbEven = (u16)(psbEven + d * ((c * acv - dispSizeY) - dispPosY));
    } else {
        actualPrbOdd = (u16)(prbEven + d * dispPosY);
        actualPsbOdd = (u16)(psbEven + d * ((c * acv - dispSizeY) - dispPosY));
        actualPrbEven = (u16)(prbOdd + d * dispPosY);
        actualPsbEven = (u16)(psbOdd + d * ((c * acv - dispSizeY) - dispPosY));
    }

    actualAcv = (u16)(dispSizeY / c);

    if (black) {
        actualPrbOdd += 2 * actualAcv - 2;
        actualPsbOdd += 2;
        actualPrbEven += 2 * actualAcv - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }

    regs[0] = (u16)(equ | (actualAcv << 4));
    MARK_CHANGED(0x00);
    regs[7] = actualPrbOdd;
    MARK_CHANGED(0x07);
    regs[6] = actualPsbOdd;
    MARK_CHANGED(0x06);
    regs[9] = actualPrbEven;
    MARK_CHANGED(0x09);
    regs[8] = actualPsbEven;
    MARK_CHANGED(0x08);
}
