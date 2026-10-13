typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef int BOOL;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
/* runtime 64-bit shift helpers (__shr2u / __shl2i); the u64 occupies the
 * hi/lo argument register pair */
extern u64 fn_800F6218(u64 value, u32 shift);
extern u64 fn_800F61F4(u32 hi, u32 lo, u32 shift);

extern u16 lbl_80641AC8[];          /* regs */
extern u16 lbl_80641B40[];          /* shdwRegs */
extern volatile u32 lbl_8064DA64;   /* flushFlag */
extern volatile u32 lbl_8064DA80;   /* changeMode */
extern volatile u64 lbl_8064DA88;   /* changed */
extern volatile u32 lbl_8064DA90;   /* shdwChangeMode */
extern volatile u64 lbl_8064DA98;   /* shdwChanged */

/* 1ull << (63 - index), split into hi/lo words */
#define VI_BITMASK(index) fn_800F61F4(0, 1, 63 - (index))

static inline s32 cntlzd(u64 bit) {
    u32 hi, lo;
    s32 value;

    hi = (u32)fn_800F6218(bit, 32);
    lo = (u32)(bit & 0xFFFFFFFF);
    value = __cntlzw(hi);
    if (value < 32) {
        return value;
    }
    return 32 + __cntlzw(lo);
}

/* VIFlush */
void fn_80217F88(void) {
    BOOL enabled;
    s32 regIndex;

    enabled = OSDisableInterrupts();
    lbl_8064DA90 |= lbl_8064DA80;
    lbl_8064DA80 = 0;
    lbl_8064DA98 |= lbl_8064DA88;

    while (lbl_8064DA88) {
        regIndex = cntlzd(lbl_8064DA88);
        lbl_80641B40[regIndex] = lbl_80641AC8[regIndex];
        lbl_8064DA88 &= ~VI_BITMASK(regIndex);
    }

    lbl_8064DA64 = 1;
    OSRestoreInterrupts(enabled);
}
