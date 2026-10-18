typedef unsigned long u32;
typedef long long s64;
typedef unsigned long long u64;
typedef u64 OSTime;

extern volatile u32 *__piReg;
OSTime OSGetTime(void);
void __GXCleanGPFifo(void);

/* Pulse PI register 0x18 (GX abort-style): set, wait 50 ticks, clear, wait 5 ticks. */
void __GXAbortWaitPECopyDone(void) {
    OSTime start;

    __piReg[6] = 1;
    start = OSGetTime();
    while ((s64)(OSGetTime() - start) <= 50) {
    }

    __piReg[6] = 0;
    start = OSGetTime();
    while ((s64)(OSGetTime() - start) <= 5) {
    }

    __GXCleanGPFifo();
}
