typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef void (*CardCallback)(s32 channel, s32 result);
typedef void (*EXICallback)(s32 channel, void *context);

typedef struct CardControl {
    BOOL attached;
    s32 result;
    u8 reserved08[0x1C];
    s32 mountStep;
    u8 reserved28[0x58];
    void *workArea;
    void *currentDir;
    void *currentFat;
    u8 reserved8C[0x38];
    CardCallback extCallback;
    u8 reservedC8[4];
    EXICallback exiCallback;
    CardCallback apiCallback;
    u8 reservedD4[8];
    CardCallback unlockCallback;
    u8 alarm[0x30];
} CardControl;

extern CardControl __CARDBlock[];
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 EXIGetState(s32 channel);
extern BOOL EXIAttach(s32 channel, EXICallback callback);
extern EXICallback EXISetExiCallback(s32 channel, EXICallback callback);
extern void OSCancelAlarm(void *alarm);
extern BOOL EXILock(s32 channel, u32 device, EXICallback unlockedCallback);
extern void __CARDDefaultApiCallback(s32 channel, s32 result);
extern void __CARDExtHandler(s32 channel, void *context);
extern void __CARDUnlockedHandler(s32 channel, void *context);
extern void __CARDMountCallback(s32 channel, s32 result);
extern s32 DoMount(s32 channel);

s32 CARDMountAsync(s32 channel, void *workArea, CardCallback detachCallback, CardCallback attachCallback)
{
    CardControl *card;
    BOOL enabled;

    if (channel < 0 || channel >= 2) {
        return -128;
    }
    if (*(u8 *)0x800030E3 & 0x80) {
        return -3;
    }

    card = &__CARDBlock[channel];
    enabled = OSDisableInterrupts();
    if (card->result == -1) {
        OSRestoreInterrupts(enabled);
        return -1;
    }
    if (!card->attached && (EXIGetState(channel) & 8)) {
        OSRestoreInterrupts(enabled);
        return -2;
    }

    card->result = -1;
    card->workArea = workArea;
    card->extCallback = detachCallback;
    card->apiCallback = attachCallback ? attachCallback : __CARDDefaultApiCallback;
    card->exiCallback = 0;

    if (!card->attached && !EXIAttach(channel, __CARDExtHandler)) {
        card->result = -3;
        OSRestoreInterrupts(enabled);
        return -3;
    }

    card->mountStep = 0;
    card->attached = 1;
    EXISetExiCallback(channel, 0);
    OSCancelAlarm(card->alarm);
    card->currentDir = 0;
    card->currentFat = 0;
    OSRestoreInterrupts(enabled);

    card->unlockCallback = __CARDMountCallback;
    if (!EXILock(channel, 0, __CARDUnlockedHandler)) {
        return 0;
    }
    card->unlockCallback = 0;
    return DoMount(channel);
}
