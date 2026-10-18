typedef unsigned char u8;
typedef signed int s32;
typedef int BOOL;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0xDC];
    CardCallback callback;
    u8 padE0[0x110 - 0xE0];
} CardControl;

extern CardControl __CARDBlock[];
extern BOOL EXIProbe(s32 chan);

void __CARDUnlockedHandler(s32 chan)
{
    CardControl *card = &__CARDBlock[chan];
    CardCallback callback = card->callback;

    if (callback) {
        card->callback = 0;
        callback(chan, EXIProbe(chan) ? 1 : -3);
    }
}
