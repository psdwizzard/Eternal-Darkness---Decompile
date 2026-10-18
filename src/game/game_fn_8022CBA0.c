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
    u8 pad38[0x78];
} Entry;
typedef struct Bank { Entry *base; u32 unk[3]; } Bank;

extern s32 CurrAutoSample;
extern volatile u32 CurrToken;
extern u8 magic;
extern void (*DSCB)(u32);
extern s32 PERFCurrSample;
extern s32 PERFCurrFrame;
extern Bank *PERFFrames;
extern u32 PPCMfpmc1(void);
extern u32 PPCMfpmc3(void);
extern u32 PPCMfpmc4(void);
extern void PERFGetAllMemMetrics(Entry *, s32);
extern void PERFStartAutoSample(void);
extern void PERFEndAutoSample(void);

#define ENTRIES (PERFFrames[PERFCurrFrame].base)

void PERFTokenCallback(u32 arg)
{
    u16 code = arg;
    s32 slot;
    u32 res;

    if (code < 0xE000 || ((code >> 8) & 0xF) != magic || PERFCurrSample == 0) {
        if (DSCB != 0)
            DSCB(arg);
    } else {
        if (code >= 0xF000) {
            if (CurrToken == 0xFFFF) {
                PERFEndAutoSample();
                PERFStartAutoSample();
            } else {
                slot = (u8)code;
                if ((u8)CurrToken != slot)
                    slot = (u8)CurrToken;
                ENTRIES[slot].resource0 = PPCMfpmc4();
                ENTRIES[slot].resource3 = PPCMfpmc3();
                ENTRIES[slot].flags = PPCMfpmc1();
                PERFGetAllMemMetrics(&ENTRIES[slot], 1);
                if (CurrAutoSample >= 0)
                    PERFEndAutoSample();
                CurrToken = 0xFFFF;
                PERFStartAutoSample();
            }
        } else {
            if (CurrToken < 0xFFFF) {
                slot = (u8)CurrToken;
                ENTRIES[slot].resource0 = PPCMfpmc4();
                ENTRIES[slot].resource3 = PPCMfpmc3();
                ENTRIES[slot].flags = PPCMfpmc1();
                PERFGetAllMemMetrics(&ENTRIES[slot], 1);
            } else {
                PERFEndAutoSample();
            }
            slot = (u8)code;
            ENTRIES[slot].resource3b = PPCMfpmc3();
            ENTRIES[slot].flagsb = PPCMfpmc1();
            res = PPCMfpmc4();
            ENTRIES[slot].resource2b = res;
            ENTRIES[slot].resource2 = res;
            PERFGetAllMemMetrics(&ENTRIES[slot], 0);
            CurrToken = (u16)arg;
        }
    }
}
