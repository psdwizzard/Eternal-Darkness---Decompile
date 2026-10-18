/* AISetDSPSampleRate: switch the DSP sample rate, re-initialising the SRC. */
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 AIGetDSPSampleRate(void);        /* AIGetDSPSampleRate */
extern u32 AIGetStreamSampleRate(void);        /* AIGetStreamSampleRate */
extern void AISetStreamVolLeft(u32 volume); /* AISetStreamVolLeft */
extern u32 AIGetStreamVolLeft(void);        /* AIGetStreamVolLeft */
extern void AISetStreamVolRight(u32 volume); /* AISetStreamVolRight */
extern u32 AIGetStreamVolRight(void);        /* AIGetStreamVolRight */
extern void __AI_SRC_INIT(void);       /* __AI_SRC_INIT */

volatile u32 __AIRegs[8] : 0xCC006C00;

void AISetDSPSampleRate(u32 rate)
{
    u32 playState;
    BOOL level;
    u32 streamRate;
    u32 left;
    u32 right;

    if (rate != AIGetDSPSampleRate()) {
        __AIRegs[0] &= ~0x40;
        if (rate == 0) {
            left = AIGetStreamVolLeft();
            right = AIGetStreamVolRight();
            playState = __AIRegs[0] & 1;
            streamRate = AIGetStreamSampleRate();
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            level = OSDisableInterrupts();
            __AI_SRC_INIT();
            __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
            __AIRegs[0] = (__AIRegs[0] & ~2) | (streamRate << 1);
            __AIRegs[0] = (__AIRegs[0] & ~1) | playState;
            __AIRegs[0] |= 0x40;
            OSRestoreInterrupts(level);
            AISetStreamVolLeft(left);
            AISetStreamVolRight(right);
        }
    }
}
