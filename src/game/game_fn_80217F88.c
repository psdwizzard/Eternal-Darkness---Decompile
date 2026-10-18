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
extern u64 __shl2i(u32 hi, u32 lo, u32 shift);

extern u16 lbl_80641AC8[];          /* regs */
extern u16 shdwRegs[];          /* shdwRegs */
extern volatile u32 flushFlag;   /* flushFlag */
extern volatile u32 changeMode;   /* changeMode */
extern volatile u64 changed;   /* changed */
extern volatile u32 shdwChangeMode;   /* shdwChangeMode */
extern volatile u64 shdwChanged;   /* shdwChanged */

/* 1ull << (63 - index), split into hi/lo words */
#define VI_BITMASK(index) __shl2i(0, 1, 63 - (index))

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
void VIFlush(void) {
    BOOL enabled;
    s32 regIndex;

    enabled = OSDisableInterrupts();
    shdwChangeMode |= changeMode;
    changeMode = 0;
    shdwChanged |= changed;

    while (changed) {
        regIndex = cntlzd(changed);
        shdwRegs[regIndex] = lbl_80641AC8[regIndex];
        changed &= ~VI_BITMASK(regIndex);
    }

    flushFlag = 1;
    OSRestoreInterrupts(enabled);
}
