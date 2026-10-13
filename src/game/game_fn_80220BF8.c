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

extern CardControl lbl_80641C60[];
extern void *memcpy(void *, const void *, unsigned long);
extern s32 fn_8021D108(s32 channel, u32 address, CardCallback callback);
extern s32 fn_8021EABC(s32 channel, u32 address, u32 length, void *data, CardCallback callback);
extern s32 fn_8021D374(CardControl *card, s32 result);

/* CARD format state machine: erase sectors, write directory/FAT blocks, then finish. */
void fn_80220BF8(s32 channel, s32 result)
{
    CardControl *card;
    CardCallback callback;

    card = &lbl_80641C60[channel];
    if (result < 0) {
        goto error;
    }

    card->formatStep++;
    if (card->formatStep < 5) {
        result = fn_8021D108(channel, card->sectorSize * card->formatStep, fn_80220BF8);
        if (result >= 0) {
            return;
        }
    } else if (card->formatStep < 10) {
        s32 step = card->formatStep - 5;
        result = fn_8021EABC(channel, card->sectorSize * step, 0x2000,
                             card->workArea + step * 0x2000, fn_80220BF8);
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
    fn_8021D374(card, result);
    callback(channel, result);
}
