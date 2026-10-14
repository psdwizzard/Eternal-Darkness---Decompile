/* fn_8021E97C: __CARDRead (Dolphin SDK CARDRead.c). */

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

extern CardControl lbl_80641C60[];
extern void fn_8021E8A0(s32 chan, s32 result);
extern s32 fn_8021CEB8(s32 chan, CardCallback callback);

s32 fn_8021E97C(s32 chan, u32 addr, u32 length, void *buffer,
                CardCallback callback)
{
    CardControl *card = &lbl_80641C60[chan];

    if (!card->attached) {
        return -3;
    }

    card->xferCallback = callback;
    card->repeat = length >> 9;
    card->addr = addr;
    card->buffer = buffer;
    return fn_8021CEB8(chan, fn_8021E8A0);
}
