/* fn_8021E8A0: ReadCallback (Dolphin SDK CARDRead.c). */

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

extern CardControl lbl_80641C60[];

extern s32 fn_8021CEB8(s32 chan, CardCallback callback); /* __CARDReadSegment */
extern s32 fn_8021D374(CardControl *card, s32 result);   /* __CARDPutControlBlock */

void fn_8021E8A0(s32 chan, s32 result)
{
    CardControl *card;
    CardCallback callback;

    card = &lbl_80641C60[chan];
    if (result < 0) {
        goto error;
    }

    card->xferred += 0x200;
    card->addr += 0x200;
    card->buffer = (u8 *)card->buffer + 0x200;
    if (--card->repeat <= 0) {
        goto error;
    }

    result = fn_8021CEB8(chan, fn_8021E8A0);
    if (result >= 0) {
        return;
    }

error:
    if (card->apiCallback == 0) {
        fn_8021D374(card, result);
    }

    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}
