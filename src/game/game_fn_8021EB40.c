/* fn_8021EB40 (0x8021EB40, 212 bytes): CARDBlock WriteCallback. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad04[0x7c];
    void *workArea;
    u8 pad84[0x4];
    void *currentFat;
    u8 pad8C[0x44];
    CARDCallback apiCallback;
    u8 padD4[0x4];
    CARDCallback eraseCallback;
    u8 padDC[0x34];
} CARDControl;

extern CARDControl lbl_80641C60[];
extern void *memcpy(void *, const void *, u32);
extern s32 fn_8021D374(CARDControl *card, s32 result); /* __CARDPutControlBlock */

void fn_8021EB40(s32 chan, s32 result)
{
    CARDControl *card;
    CARDCallback callback;
    u16 *fat0;
    u16 *fat1;

    card = &lbl_80641C60[chan];
    if (result >= 0) {
        fat0 = (u16 *)((u8 *)card->workArea + 0x6000);
        fat1 = (u16 *)((u8 *)card->workArea + 0x8000);
        if (card->currentFat == fat0) {
            card->currentFat = fat1;
            memcpy(fat1, fat0, 0x2000);
        } else {
            card->currentFat = fat0;
            memcpy(fat0, fat1, 0x2000);
        }
    }

    if (card->apiCallback == 0)
        fn_8021D374(card, result);

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
