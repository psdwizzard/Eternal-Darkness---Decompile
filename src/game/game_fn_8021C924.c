/* TimeoutHandler: TimeoutHandler (Dolphin SDK CARDBios.c). */

typedef unsigned char u8;
typedef signed int s32;

typedef void (*CardCallback)(s32 channel, s32 result);
typedef void (*EXICallback)(s32 chan, void *context);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    s32 attached;
    u8 pad04[0xCC - 0x04];
    CardCallback exiCallback;
    u8 padD0[0xE0 - 0xD0];
    u8 alarm[0x30];
} CardControl;

extern CardControl __CARDBlock[];

extern EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback);

void TimeoutHandler(void *alarm, void *context)
{
    s32 chan;
    CardControl *card;
    CardCallback callback;

    for (chan = 0; chan < 2; ++chan) {
        card = &__CARDBlock[chan];
        if (alarm == &card->alarm) {
            break;
        }
    }

    if (!card->attached) {
        return;
    }

    EXISetExiCallback(chan, 0);
    callback = card->exiCallback;
    if (callback) {
        card->exiCallback = 0;
        callback(chan, -5);
    }
}
