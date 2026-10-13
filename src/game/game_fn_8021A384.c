/* AISetStreamSampleRate: change the streaming sample rate, muting and re-initialising the SRC. */
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void fn_8021A1A8(u32 state);  /* AISetStreamPlayState */
extern u32 fn_8021A458(void);        /* AIGetStreamSampleRate */
extern void fn_8021A468(u32 volume); /* AISetStreamVolLeft */
extern u32 fn_8021A484(void);        /* AIGetStreamVolLeft */
extern void fn_8021A494(u32 volume); /* AISetStreamVolRight */
extern u32 fn_8021A4B0(void);        /* AIGetStreamVolRight */
extern void fn_8021A788(void);       /* __AI_SRC_INIT */

volatile u32 __AIRegs[8] : 0xCC006C00;

/* AIGetStreamPlayState, inlined here */
static inline u32 GetStreamPlayState(void)
{
    return __AIRegs[0] & 1;
}

void fn_8021A384(u32 rate)
{
    BOOL level;
    u32 playState;
    u32 volLeft;
    u32 volRight;
    u32 dspState;

    if (rate == fn_8021A458()) {
        return;
    }
    playState = GetStreamPlayState();
    volLeft = fn_8021A484();
    volRight = fn_8021A4B0();
    fn_8021A494(0);
    fn_8021A468(0);
    dspState = __AIRegs[0] & 0x40;
    __AIRegs[0] = __AIRegs[0] & ~0x40;
    level = OSDisableInterrupts();
    fn_8021A788();
    __AIRegs[0] |= dspState;
    __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
    __AIRegs[0] = (__AIRegs[0] & ~2) | (rate << 1);
    OSRestoreInterrupts(level);
    fn_8021A1A8(playState);
    fn_8021A468(volLeft);
    fn_8021A494(volRight);
}
