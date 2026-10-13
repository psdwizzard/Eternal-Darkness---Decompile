/* fn_8021F014: EraseCallback (Dolphin SDK CARDDir.c). */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0xC];
    s32 sectorSize;
    u8 pad10[0x80 - 0x10];
    void *workArea;
    void *currentDir;
    u8 pad88[0xD0 - 0x88];
    CardCallback apiCallback;
    u8 padD4[4];
    CardCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CardControl;

extern CardControl lbl_80641C60[];

extern s32 fn_8021D374(CardControl *card, s32 result);
extern s32 fn_8021EABC(s32 chan, u32 addr, s32 length, void *dst, CardCallback callback);
extern void fn_8021EF44(s32 chan, s32 result);

static inline void *GetDirectoryBlock(CardControl *card)
{
    void *dir = card->currentDir;
    return dir;
}

void fn_8021F014(s32 chan, s32 result)
{
    CardControl *card;
    CardCallback callback;
    void *dir;
    u32 addr;

    card = &lbl_80641C60[chan];
    if (result < 0) {
        goto error;
    }

    dir = GetDirectoryBlock(card);
    addr = ((u32)dir - (u32)card->workArea) / 0x2000 * card->sectorSize;
    result = fn_8021EABC(chan, addr, 0x2000, dir, fn_8021EF44);
    if (result < 0) {
        goto error;
    }
    return;

error:
    if (card->apiCallback == 0) {
        fn_8021D374(card, result);
    }

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
