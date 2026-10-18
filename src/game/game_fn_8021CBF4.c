/* Retry a memory card command once its EXI channel becomes available. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef void (*CardCallback)(s32 channel, s32 result);
typedef void (*EXICallback)(s32 channel, void *context);

typedef struct CardControl {
    u8 reserved00[0x94];
    u8 cmd[9];
    u8 reserved9D[0xC8 - 0x9D];
    CardCallback txCallback;
    CardCallback exiCallback;
    u8 reservedD0[0xC];
    CardCallback unlockCallback;
    u8 reservedE0[0x30];
} CardControl;

extern CardControl __CARDBlock[];
extern s32 EXILock(s32 channel, u32 device, EXICallback unlockedCallback);
extern void __CARDUnlockedHandler(s32 channel, void *context);
extern s32 Retry(s32 channel);

void UnlockedCallback(s32 channel, s32 result)
{
    CardControl *card = &__CARDBlock[channel];
    CardCallback callback;

    if (result >= 0) {
        card->unlockCallback = UnlockedCallback;
        if (!EXILock(channel, 0, __CARDUnlockedHandler)) {
            result = 0;
        } else {
            card->unlockCallback = 0;
            result = Retry(channel);
        }
    }

    if (result < 0) {
        switch (card->cmd[0]) {
        case 0x52:
            callback = card->txCallback;
            if (callback) {
                card->txCallback = 0;
                callback(channel, result);
            }
            break;
        case 0xF1:
        case 0xF2:
        case 0xF4:
            callback = card->exiCallback;
            if (callback) {
                card->exiCallback = 0;
                callback(channel, result);
            }
            break;
        }
    }
}
