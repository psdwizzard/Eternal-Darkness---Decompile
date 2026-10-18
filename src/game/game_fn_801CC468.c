typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DSPvoice {
    u8 pad00[0x24];
    u32 changed[5];
    u8 pad38[0xBC];
} DSPvoice;

extern u8 sndActive;
extern DSPvoice* volatile dspVoice;
extern u8 salNumVoices;
extern u8 salAuxFrame;
extern u8 salFrame;

extern void streamCorrectLoops(void);
extern void hwIRQEnterCritical(void);
extern void salAiGetDest(void);
extern void salCtrlDsp(void);
extern void hwIRQLeaveCritical(void);
extern void salHandleAuxProcessing(void);
extern void hwSetTimeOffset(u32);
extern void seqHandle(u32);
extern void synthHandle(u32);
extern void s3dHandle(void);
extern void fn_801B941C(void);
extern void vsSampleUpdates(void);

void snd_handle_irq(void)
{
    u32 timeOffset;
    u8 voiceIndex;
    u8 i;

    if (sndActive == 0) {
        return;
    }

    streamCorrectLoops();
    hwIRQEnterCritical();
    salAiGetDest();
    salCtrlDsp();
    hwIRQLeaveCritical();
    hwIRQEnterCritical();
    salHandleAuxProcessing();
    hwIRQLeaveCritical();
    hwIRQEnterCritical();

    salFrame ^= 1;
    salAuxFrame = (salAuxFrame + 1) % 3;

    for (voiceIndex = 0; voiceIndex < salNumVoices; voiceIndex++) {
        for (i = 0; i < 5; i++) {
            dspVoice[voiceIndex].changed[i] = 0;
        }
    }

    hwIRQLeaveCritical();

    for (timeOffset = 0; (u8)timeOffset < 5; timeOffset++) {
        hwIRQEnterCritical();
        hwSetTimeOffset(timeOffset);
        seqHandle(0x100);
        synthHandle(0x100);
        hwIRQLeaveCritical();
    }

    hwIRQEnterCritical();
    hwSetTimeOffset(0);
    s3dHandle();
    hwIRQLeaveCritical();
    hwIRQEnterCritical();
    fn_801B941C();
    hwIRQLeaveCritical();
    hwIRQEnterCritical();
    vsSampleUpdates();
    hwIRQLeaveCritical();
}
