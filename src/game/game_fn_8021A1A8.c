/* AISetStreamPlayState: start/stop streaming, re-initialising the SRC when starting at 32kHz. */
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 AIGetStreamPlayState(void);        /* AIGetStreamPlayState */
extern u32 AIGetStreamSampleRate(void);        /* AIGetStreamSampleRate */
extern void AISetStreamVolLeft(u32 volume); /* AISetStreamVolLeft */
extern u32 AIGetStreamVolLeft(void);        /* AIGetStreamVolLeft */
extern void AISetStreamVolRight(u32 volume); /* AISetStreamVolRight */
extern u32 AIGetStreamVolRight(void);        /* AIGetStreamVolRight */
extern void __AI_SRC_INIT(void);       /* __AI_SRC_INIT */

volatile u32 __AIRegs[8] : 0xCC006C00;

void AISetStreamPlayState(u32 state)
{
    BOOL level;
    u32 volRight;
    u32 volLeft;

    if (state == AIGetStreamPlayState()) {
        return;
    }
    if (AIGetStreamSampleRate() == 0 && state == 1) {
        volRight = AIGetStreamVolRight();
        volLeft = AIGetStreamVolLeft();
        AISetStreamVolRight(0);
        AISetStreamVolLeft(0);
        level = OSDisableInterrupts();
        __AI_SRC_INIT();
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AIRegs[0] = (__AIRegs[0] & ~1) | 1;
        OSRestoreInterrupts(level);
        AISetStreamVolLeft(volRight);
        AISetStreamVolRight(volLeft);
    } else {
        __AIRegs[0] = (__AIRegs[0] & ~1) | state;
    }
}
