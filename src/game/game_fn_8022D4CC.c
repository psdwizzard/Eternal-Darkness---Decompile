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

/* Interrupt-visible profiler state: PERFStartAutoSampling installs this function as
 * an OS alarm callback. PERFStartFrame also installs PERFTokenCallback via GXSetDrawSyncCallback
 * as the PE token callback, dispatched by GXTokenInterruptHandler. That callback checks
 * the bank discriminator (DBD8), changes the token (C4B4), and calls the
 * entry start/finish routines, which update C4B0 and DBE0. The allocation
 * parameters below are not changed by the token callback. */
extern volatile s32 CurrAutoSample;
extern volatile u32 CurrToken;
extern volatile u8 magic;
extern volatile s32 PERFCurrSample;
extern s32 PERFCurrFrame;
extern Bank *PERFFrames;
extern s32 PERFNumSamples;
extern const char lbl_802FF7EC[];
extern u32 PPCMfpmc1(void);
extern u32 PPCMfpmc3(void);
extern u32 PPCMfpmc4(void);
extern void PERFGetAllMemMetrics(Entry *, s32);
extern void OSReport(const char *, ...);
extern void *memcpy(void *, const void *, u32);

#define ENTRY_AT(n) (PERFFrames[PERFCurrFrame].base[(n)])

static inline s32 AllocateEntry(void)
{
    if ((u32)PERFCurrSample >= (u32)(PERFNumSamples - 1)) {
        PERFCurrSample = PERFNumSamples - 1;
        return PERFCurrSample;
    }
    return PERFCurrSample++;
}

static inline void FinishEntry(void)
{
    if (CurrAutoSample >= 0) {
        ENTRY_AT(CurrAutoSample).resource0 = PPCMfpmc4();
        PERFGetAllMemMetrics(&ENTRY_AT(CurrAutoSample), 1);
        ENTRY_AT(CurrAutoSample).resource3 = PPCMfpmc3();
        ENTRY_AT(CurrAutoSample).flags = PPCMfpmc1();
    }
    CurrAutoSample = -1;
}

static inline void StartEntry(void)
{
    CurrAutoSample = AllocateEntry();
    ENTRY_AT(CurrAutoSample).state = 0xFF;
    ENTRY_AT(CurrAutoSample).status = 0;
    PERFGetAllMemMetrics(&ENTRY_AT(CurrAutoSample), 0);
    ENTRY_AT(CurrAutoSample).resource2 = PPCMfpmc4();
    ENTRY_AT(CurrAutoSample).resource0 = 0;
    ENTRY_AT(CurrAutoSample).resource3b = PPCMfpmc3();
    ENTRY_AT(CurrAutoSample).flagsb = PPCMfpmc1();
}

/* Decode the entry index and return the bank encoded in the token. */
static inline s32 DecodeToken(s32 *source)
{
    *source = CurrToken & 0xFF;
    return (CurrToken >> 8) & 0xF;
}

void PERFTimerCallback(void)
{
    s32 source;
    s32 slot;
    s32 bank;
    if (PERFCurrSample == 0)
        return;
    if (CurrToken < 0xFFFF) {
        bank = DecodeToken(&source);
        if (bank != magic) {
            FinishEntry();
            StartEntry();
            return;
        }
        slot = AllocateEntry();
        memcpy(&ENTRY_AT(slot), &ENTRY_AT(source), sizeof(Entry));
        ENTRY_AT(slot).resource0 = PPCMfpmc4();
        ENTRY_AT(slot).resource3 = PPCMfpmc3();
        ENTRY_AT(slot).flags = PPCMfpmc1();
        PERFGetAllMemMetrics(&ENTRY_AT(slot), 1);
        ENTRY_AT(slot).state = 0xFF;
        ENTRY_AT(source).resource2 = PPCMfpmc4();
        ENTRY_AT(source).resource3b = PPCMfpmc3();
        ENTRY_AT(source).flagsb = PPCMfpmc1();
        PERFGetAllMemMetrics(&ENTRY_AT(source), 0);
        ENTRY_AT(source).status = 1;
        CurrAutoSample = -1;
        return;
    }
    if (CurrAutoSample < 0) {
        OSReport(lbl_802FF7EC);
        return;
    }
    FinishEntry();
    StartEntry();
}
