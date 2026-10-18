/* __CARDReadSegment: __CARDReadSegment (Dolphin SDK CARDRdwr.c). */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0x14];
    s32 latency;
    u8 pad18[0x80 - 0x18];
    u8 *workArea;
    u8 pad84[0x94 - 0x84];
    u8 cmd[9];
    u8 pad9D[0xA0 - 0x9D];
    s32 cmdlen;
    u32 mode;
    s32 retry;
    u8 padAC[4];
    u32 addr;
    void *buffer;
    u8 padB8[0xC8 - 0xB8];
    CardCallback txCallback;
    u8 padCC[0x110 - 0xCC];
} CardControl;

extern CardControl __CARDBlock[];

extern s32 __CARDStart(s32 chan, CardCallback txCallback, CardCallback exiCallback);
extern BOOL EXIImmEx(s32 chan, void *buf, s32 len, u32 type);
extern BOOL EXIDma(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXIUnlock(s32 chan);
extern void __CARDTxHandler(s32 chan, void *context);

s32 __CARDReadSegment(s32 chan, CardCallback callback)
{
    CardControl *card;
    s32 result;

    card = &__CARDBlock[chan];
    card->cmd[0] = 0x52;
    card->cmd[1] = (u8)((card->addr >> 17) & 0x7F);
    card->cmd[2] = (u8)(card->addr >> 9);
    card->cmd[3] = (u8)((card->addr >> 7) & 3);
    card->cmd[4] = (u8)(card->addr & 0x7F);
    card->cmdlen = 5;
    card->mode = 0;
    card->retry = 0;

    result = __CARDStart(chan, callback, 0);
    if (result == -1) {
        result = 0;
    } else if (result >= 0) {
        if (!EXIImmEx(chan, card->cmd, card->cmdlen, 1) ||
            !EXIImmEx(chan, card->workArea + 0x200, card->latency, 1) ||
            !EXIDma(chan, card->buffer, 0x200, card->mode, __CARDTxHandler)) {
            card->txCallback = 0;
            EXIDeselect(chan);
            EXIUnlock(chan);
            result = -3;
        } else {
            result = 0;
        }
    }
    return result;
}
