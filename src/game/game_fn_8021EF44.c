/* fn_8021EF44: WriteCallback (Dolphin SDK CARDDir.c). */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0x80];
    void *workArea;
    void *currentDir;
    u8 pad88[0xD0 - 0x88];
    CardCallback apiCallback;
    u8 padD4[4];
    CardCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CardControl;

extern CardControl __CARDBlock[];

extern void *memcpy(void *dst, const void *src, unsigned long n);
extern s32 __CARDPutControlBlock(CardControl *card, s32 result);

void fn_8021EF44(s32 chan, s32 result)
{
    CardControl *card;
    CardCallback callback;

    card = &__CARDBlock[chan];
    if (0 <= result) {
        void *dir0 = (u8 *)card->workArea + 0x2000;
        void *dir1 = (u8 *)card->workArea + 0x4000;

        if (card->currentDir == dir0) {
            card->currentDir = dir1;
            memcpy(dir1, dir0, 0x2000);
        } else {
            card->currentDir = dir0;
            memcpy(dir0, dir1, 0x2000);
        }
    }

    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
