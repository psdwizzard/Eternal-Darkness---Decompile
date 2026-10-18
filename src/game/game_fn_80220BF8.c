typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    BOOL attached;
    s32 result;
    u8 reserved08[4];
    s32 sectorSize;
    u8 reserved10[0x18];
    s32 formatStep;
    u8 reserved2C[0x54];
    u8 *workArea;
    void *currentDir;
    void *currentFat;
    u8 reserved8C[0x44];
    CardCallback apiCallback;
    u8 reservedD4[0x3C];
} CardControl;

extern CardControl __CARDBlock[];
extern void *memcpy(void *, const void *, unsigned long);
extern s32 __CARDEraseSector(s32 channel, u32 address, CardCallback callback);
extern s32 __CARDWrite(s32 channel, u32 address, u32 length, void *data, CardCallback callback);
extern s32 __CARDPutControlBlock(CardControl *card, s32 result);

/* CARD format state machine: erase sectors, write directory/FAT blocks, then finish. */
void FormatCallback(s32 channel, s32 result)
{
    CardControl *card;
    CardCallback callback;

    card = &__CARDBlock[channel];
    if (result < 0) {
        goto error;
    }

    card->formatStep++;
    if (card->formatStep < 5) {
        result = __CARDEraseSector(channel, card->sectorSize * card->formatStep, FormatCallback);
        if (result >= 0) {
            return;
        }
    } else if (card->formatStep < 10) {
        s32 step = card->formatStep - 5;
        result = __CARDWrite(channel, card->sectorSize * step, 0x2000,
                             card->workArea + step * 0x2000, FormatCallback);
        if (result >= 0) {
            return;
        }
    } else {
        card->currentDir = card->workArea + 0x2000;
        memcpy(card->currentDir, card->workArea + 0x4000, 0x2000);
        card->currentFat = card->workArea + 0x6000;
        memcpy(card->currentFat, card->workArea + 0x8000, 0x2000);
    }

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(channel, result);
}
