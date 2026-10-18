/* __CARDWrite: start a transfer in 128-byte pages. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    s32 attached;
    u8 pad04[0xAC - 0x04];
    u32 repeat;
    u32 addr;
    void *buffer;
    u8 padB8[0xD4 - 0xB8];
    CardCallback transferCallback;
    u8 padD8[0x110 - 0xD8];
} CardControl;

extern CardControl __CARDBlock[];
extern void BlockWriteCallback(s32 channel, s32 result);
extern s32 __CARDWritePage(s32 channel, CardCallback callback);

s32 __CARDWrite(s32 channel, u32 address, u32 length, void *buffer,
                CardCallback callback)
{
    CardControl *card = &__CARDBlock[channel];

    if (!card->attached) {
        return -3;
    }
    card->transferCallback = callback;
    card->repeat = length >> 7;
    card->addr = address;
    card->buffer = buffer;
    return __CARDWritePage(channel, BlockWriteCallback);
}
