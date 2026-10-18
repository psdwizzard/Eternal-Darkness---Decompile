/* __CARDRead: __CARDRead (Dolphin SDK CARDRead.c). */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    s32 attached;
    u8 pad04[0xAC - 0x04];
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
extern void BlockReadCallback(s32 chan, s32 result);
extern s32 __CARDReadSegment(s32 chan, CardCallback callback);

s32 __CARDRead(s32 chan, u32 addr, u32 length, void *buffer,
                CardCallback callback)
{
    CardControl *card = &__CARDBlock[chan];

    if (!card->attached) {
        return -3;
    }

    card->xferCallback = callback;
    card->repeat = length >> 9;
    card->addr = addr;
    card->buffer = buffer;
    return __CARDReadSegment(chan, BlockReadCallback);
}
