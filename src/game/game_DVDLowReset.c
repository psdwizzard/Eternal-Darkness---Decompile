typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed long long OSTime;

extern u64 __OSGetSystemTime(void);
extern volatile u32 ResetOccurred_8064D9B0;
extern volatile OSTime LastResetEnd_8064D9A8;

volatile u32 __DIRegs[16] : 0xCC006000;
volatile u32 __PIRegs[12] : 0xCC003000;
extern u32 __OSBusClock : 0x800000F8;
#define OS_TIMER_CLOCK (__OSBusClock / 4)
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

void DVDLowReset(void)
{
    u32 reset;
    OSTime start;

    __DIRegs[1] = 2;
    reset = __PIRegs[9];
    __PIRegs[9] = (reset & ~4) | 1;

    /* The timer returns unsigned ticks; the reset delay uses signed elapsed time. */
    start = (OSTime)__OSGetSystemTime();
    while ((OSTime)__OSGetSystemTime() - start < OSMicrosecondsToTicks(12)) {
    }

    __PIRegs[9] = reset | 5;
    ResetOccurred_8064D9B0 = 1;
    LastResetEnd_8064D9A8 = (OSTime)__OSGetSystemTime();
}
