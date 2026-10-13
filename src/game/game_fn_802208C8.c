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

extern CardControl lbl_80641C60[];
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 fn_80207C88(s32 channel);
extern BOOL fn_802071F8(s32 channel, EXICallback callback);
extern EXICallback fn_80206ED4(s32 channel, EXICallback callback);
extern void fn_8020A93C(void *alarm);
extern BOOL EXILock(s32 channel, u32 device, EXICallback unlockedCallback);
extern void fn_8021C374(s32 channel, s32 result);
extern void fn_8021C3AC(s32 channel, void *context);
extern void fn_8021C644(s32 channel, void *context);
extern void fn_802207C0(s32 channel, s32 result);
extern s32 fn_802203B0(s32 channel);

s32 fn_802208C8(s32 channel, void *workArea, CardCallback detachCallback, CardCallback attachCallback)
{
    CardControl *card;
    BOOL enabled;

    if (channel < 0 || channel >= 2) {
        return -128;
    }
    if (*(u8 *)0x800030E3 & 0x80) {
        return -3;
    }

    card = &lbl_80641C60[channel];
    enabled = OSDisableInterrupts();
    if (card->result == -1) {
        OSRestoreInterrupts(enabled);
        return -1;
    }
    if (!card->attached && (fn_80207C88(channel) & 8)) {
        OSRestoreInterrupts(enabled);
        return -2;
    }

    card->result = -1;
    card->workArea = workArea;
    card->extCallback = detachCallback;
    card->apiCallback = attachCallback ? attachCallback : fn_8021C374;
    card->exiCallback = 0;

    if (!card->attached && !fn_802071F8(channel, fn_8021C3AC)) {
        card->result = -3;
        OSRestoreInterrupts(enabled);
        return -3;
    }

    card->mountStep = 0;
    card->attached = 1;
    fn_80206ED4(channel, 0);
    fn_8020A93C(card->alarm);
    card->currentDir = 0;
    card->currentFat = 0;
    OSRestoreInterrupts(enabled);

    card->unlockCallback = fn_802207C0;
    if (!EXILock(channel, 0, fn_8021C644)) {
        return 0;
    }
    card->unlockCallback = 0;
    return fn_802203B0(channel);
}
