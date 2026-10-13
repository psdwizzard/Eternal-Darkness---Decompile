/* AISetStreamPlayState: start/stop streaming, re-initialising the SRC when starting at 32kHz. */
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 fn_8021A280(void);        /* AIGetStreamPlayState */
extern u32 fn_8021A458(void);        /* AIGetStreamSampleRate */
extern void fn_8021A468(u32 volume); /* AISetStreamVolLeft */
extern u32 fn_8021A484(void);        /* AIGetStreamVolLeft */
extern void fn_8021A494(u32 volume); /* AISetStreamVolRight */
extern u32 fn_8021A4B0(void);        /* AIGetStreamVolRight */
extern void fn_8021A788(void);       /* __AI_SRC_INIT */

volatile u32 __AIRegs[8] : 0xCC006C00;

void fn_8021A1A8(u32 state)
{
    BOOL level;
    u32 volRight;
    u32 volLeft;

    if (state == fn_8021A280()) {
        return;
    }
    if (fn_8021A458() == 0 && state == 1) {
        volRight = fn_8021A4B0();
        volLeft = fn_8021A484();
        fn_8021A494(0);
        fn_8021A468(0);
        level = OSDisableInterrupts();
        fn_8021A788();
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AIRegs[0] = (__AIRegs[0] & ~1) | 1;
        OSRestoreInterrupts(level);
        fn_8021A468(volRight);
        fn_8021A494(volLeft);
    } else {
        __AIRegs[0] = (__AIRegs[0] & ~1) | state;
    }
}
