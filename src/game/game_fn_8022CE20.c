typedef unsigned int u32;
typedef int s32;

typedef struct Entry Entry;
typedef struct Bank {
    Entry *base;
    u32 active;
    u32 unk[2];
} Bank;

typedef void (*Callback)(u32);

extern volatile s32 PERFCurrSample;
extern volatile u32 CurrToken;
extern s32 PERFCurrFrame;
extern Bank *PERFFrames;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern Callback GXSetDrawSyncCallback(Callback);
extern void PERFTokenCallback(u32);
extern void PERFResetAllMemMetrics(void);
extern void GXClearGPMetric(void);
extern void PPCMtpmc1(u32);
extern void PPCMtpmc2(u32);
extern void PPCMtpmc3(u32);
extern void PPCMtpmc4(u32);
extern void PPCMtmmcr0(int);
extern void PPCMtmmcr1(int);
extern void PERFStartAutoSample(void);

void PERFStartFrame(void)
{
    s32 enabled = OSDisableInterrupts();

    PERFCurrSample = 0;
    CurrToken = 0xFFFF;
    GXSetDrawSyncCallback(PERFTokenCallback);
    PERFFrames[PERFCurrFrame].active = 0;
    PERFResetAllMemMetrics();
    GXClearGPMetric();
    PPCMtpmc1(0);
    PPCMtpmc2(0);
    PPCMtpmc3(0);
    PPCMtpmc4(0);
    PPCMtmmcr0(0x8B);
    PPCMtmmcr1(0x78400000);
    PERFStartAutoSample();
    OSRestoreInterrupts(enabled);
}
