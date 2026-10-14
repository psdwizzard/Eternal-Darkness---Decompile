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

extern CardControl lbl_80641C60[];
extern BOOL fn_802070C4(s32 chan);

void fn_8021C644(s32 chan)
{
    CardControl *card = &lbl_80641C60[chan];
    CardCallback callback = card->callback;

    if (callback) {
        card->callback = 0;
        callback(chan, fn_802070C4(chan) ? 1 : -3);
    }
}
