/* BlockWriteCallback: WriteCallback (Dolphin SDK CARDWrite.c). */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0xAC];
    s32 repeat;
    u32 addr;
    void *buffer;
    s32 xferred;
    u8 padBC[0xD0 - 0xBC];
    CardCallback apiCallback;
    CardCallback xferCallback;
    u8 padD8[0x110 - 0xD8];
} CardControl;

extern CardControl __CARDBlock[];

extern s32 __CARDWritePage(s32 chan, CardCallback callback); /* __CARDWritePage */
extern s32 __CARDPutControlBlock(CardControl *card, s32 result);   /* __CARDPutControlBlock */

void BlockWriteCallback(s32 chan, s32 result)
{
    CardControl *card;
    CardCallback callback;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    card->xferred += 0x80;
    card->addr += 0x80;
    card->buffer = (u8 *)card->buffer + 0x80;
    if (--card->repeat <= 0) {
        goto error;
    }

    result = __CARDWritePage(chan, BlockWriteCallback);
    if (result >= 0) {
        return;
    }

error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }

    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}
