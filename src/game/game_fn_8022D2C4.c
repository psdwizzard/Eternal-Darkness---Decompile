typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 state;
    u8 pad01[0x0B];
    u32 resource2;
    u32 resource0;
    u32 status;
    u8 pad18[0x04];
    u32 resource2b;
    u32 resource3b;
    u32 resource3;
    u8 pad28[0x08];
    u32 flagsb;
    u32 flags;
    u8 pad38[0x08];
    u32 memoryCounters[10][2];
    u32 graphicsCounters[4][2];
} Entry;

typedef struct Bank {
    Entry *base;
    u32 unk[3];
} Bank;

extern s32 CurrAutoSample;
extern s32 PERFCurrSample;
extern s32 PERFCurrFrame;
extern Bank *PERFFrames;
extern s32 PERFNumSamples;
extern u32 PPCMfpmc1(void);
extern u32 PPCMfpmc3(void);
extern u32 PPCMfpmc4(void);
extern void PERFGetAllMemMetrics(Entry *, s32);

#define ENTRY_AT(n) (PERFFrames[PERFCurrFrame].base[(n)])

/* The entry count and current index are shared with interrupt callbacks.
 * PERFStartFrame installs PERFTokenCallback through GXSetDrawSyncCallback; the PE token
 * interrupt handler GXTokenInterruptHandler dispatches it. PERFTokenCallback calls this
 * routine and PERFEndAutoSample. The alarm callback PERFTimerCallback, registered by
 * PERFStartAutoSampling, also allocates entries and changes the current index.
 * Qualify accesses to that shared state while retaining the globals' s32
 * declarations used by the entry start/finish and token callback units. */
#define ENTRY_COUNT (*(volatile s32 *)&PERFCurrSample)
#define CURRENT_INDEX (*(volatile s32 *)&CurrAutoSample)

static inline s32 AllocateEntry(void)
{
    if ((u32)ENTRY_COUNT >= (u32)(PERFNumSamples - 1)) {
        ENTRY_COUNT = PERFNumSamples - 1;
        return ENTRY_COUNT;
    }
    return ENTRY_COUNT++;
}

void PERFStartAutoSample(void)
{
    CURRENT_INDEX = AllocateEntry();
    ENTRY_AT(CURRENT_INDEX).state = 0xFF;
    ENTRY_AT(CURRENT_INDEX).status = 0;
    PERFGetAllMemMetrics(&ENTRY_AT(CURRENT_INDEX), 0);
    ENTRY_AT(CURRENT_INDEX).resource2 = PPCMfpmc4();
    ENTRY_AT(CURRENT_INDEX).resource0 = 0;
    ENTRY_AT(CURRENT_INDEX).resource3b = PPCMfpmc3();
    ENTRY_AT(CURRENT_INDEX).flagsb = PPCMfpmc1();
}
