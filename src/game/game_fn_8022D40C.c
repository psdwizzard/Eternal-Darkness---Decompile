typedef unsigned char u8;
typedef unsigned short u16;
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
extern s32 PERFCurrFrame;
extern Bank *PERFFrames;
extern u32 PPCMfpmc1(void);
extern u32 PPCMfpmc3(void);
extern u32 PPCMfpmc4(void);
extern void PERFGetAllMemMetrics(Entry *entry, s32 sample);

#define CURRENT_ENTRY (PERFFrames[PERFCurrFrame].base[CurrAutoSample])

void PERFEndAutoSample(void)
{
    if (CurrAutoSample >= 0) {
        CURRENT_ENTRY.resource0 = PPCMfpmc4();
        PERFGetAllMemMetrics(&CURRENT_ENTRY, 1);
        CURRENT_ENTRY.resource3 = PPCMfpmc3();
        CURRENT_ENTRY.flags = PPCMfpmc1();
    }
    CurrAutoSample = -1;
}
