/* AISetDSPSampleRate: switch the DSP sample rate, re-initialising the SRC. */
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 fn_8021A370(void);        /* AIGetDSPSampleRate */
extern u32 fn_8021A458(void);        /* AIGetStreamSampleRate */
extern void fn_8021A468(u32 volume); /* AISetStreamVolLeft */
extern u32 fn_8021A484(void);        /* AIGetStreamVolLeft */
extern void fn_8021A494(u32 volume); /* AISetStreamVolRight */
extern u32 fn_8021A4B0(void);        /* AIGetStreamVolRight */
extern void fn_8021A788(void);       /* __AI_SRC_INIT */

volatile u32 __AIRegs[8] : 0xCC006C00;

void fn_8021A290(u32 rate)
{
    u32 playState;
    BOOL level;
    u32 streamRate;
    u32 left;
    u32 right;

    if (rate != fn_8021A370()) {
        __AIRegs[0] &= ~0x40;
        if (rate == 0) {
            left = fn_8021A484();
            right = fn_8021A4B0();
            playState = __AIRegs[0] & 1;
            streamRate = fn_8021A458();
            fn_8021A468(0);
            fn_8021A494(0);
            level = OSDisableInterrupts();
            fn_8021A788();
            __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
            __AIRegs[0] = (__AIRegs[0] & ~2) | (streamRate << 1);
            __AIRegs[0] = (__AIRegs[0] & ~1) | playState;
            __AIRegs[0] |= 0x40;
            OSRestoreInterrupts(level);
            fn_8021A468(left);
            fn_8021A494(right);
        }
    }
}
