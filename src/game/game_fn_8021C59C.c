typedef unsigned char u8;
typedef signed int s32;
typedef int BOOL;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0xC8];
    CardCallback txCallback;
    u8 padCC[0x110 - 0xCC];
} CardControl;

extern CardControl __CARDBlock[];
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXIUnlock(s32 chan);
extern BOOL EXIProbe(s32 chan);

/* Complete the EXI transfer and notify the pending card callback. */
void __CARDTxHandler(s32 chan, void *context)
{
    CardControl *card;
    CardCallback callback;
    BOOL err;

    card = &__CARDBlock[chan];
    err = !EXIDeselect(chan);
    EXIUnlock(chan);
    callback = card->txCallback;
    if (callback) {
        card->txCallback = 0;
        callback(chan, !err && EXIProbe(chan) ? 0 : -3);
    }
}
