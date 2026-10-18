/* AISetStreamSampleRate: change the streaming sample rate, muting and re-initialising the SRC. */
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void AISetStreamPlayState(u32 state);  /* AISetStreamPlayState */
extern u32 AIGetStreamSampleRate(void);        /* AIGetStreamSampleRate */
extern void AISetStreamVolLeft(u32 volume); /* AISetStreamVolLeft */
extern u32 AIGetStreamVolLeft(void);        /* AIGetStreamVolLeft */
extern void AISetStreamVolRight(u32 volume); /* AISetStreamVolRight */
extern u32 AIGetStreamVolRight(void);        /* AIGetStreamVolRight */
extern void __AI_SRC_INIT(void);       /* __AI_SRC_INIT */

volatile u32 __AIRegs[8] : 0xCC006C00;

/* AIGetStreamPlayState, inlined here */
static inline u32 GetStreamPlayState(void)
{
    return __AIRegs[0] & 1;
}

void __AI_set_stream_sample_rate(u32 rate)
{
    BOOL level;
    u32 playState;
    u32 volLeft;
    u32 volRight;
    u32 dspState;

    if (rate == AIGetStreamSampleRate()) {
        return;
    }
    playState = GetStreamPlayState();
    volLeft = AIGetStreamVolLeft();
    volRight = AIGetStreamVolRight();
    AISetStreamVolRight(0);
    AISetStreamVolLeft(0);
    dspState = __AIRegs[0] & 0x40;
    __AIRegs[0] = __AIRegs[0] & ~0x40;
    level = OSDisableInterrupts();
    __AI_SRC_INIT();
    __AIRegs[0] |= dspState;
    __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
    __AIRegs[0] = (__AIRegs[0] & ~2) | (rate << 1);
    OSRestoreInterrupts(level);
    AISetStreamPlayState(playState);
    AISetStreamVolLeft(volLeft);
    AISetStreamVolRight(volRight);
}
