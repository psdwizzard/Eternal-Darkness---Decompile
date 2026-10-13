/* fn_8021D108: __CARDEraseSector (Dolphin SDK CARDRdwr.c). */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef void (*CardCallback)(s32 channel, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0x94];
    u8 cmd[9];
    u8 pad9D[0xA0 - 0x9D];
    s32 cmdlen;
    u32 mode;
    s32 retry;
    u8 padAC[0xCC - 0xAC];
    CardCallback exiCallback;
    u8 padD0[0x110 - 0xD0];
} CardControl;

extern CardControl lbl_80641C60[];

extern s32 fn_8021CD04(s32 chan, CardCallback txCallback, CardCallback exiCallback);
extern BOOL fn_80206AC8(s32 chan, void *buf, s32 len, u32 type);
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXIUnlock(s32 chan);

s32 fn_8021D108(s32 chan, u32 addr, CardCallback callback)
{
    CardControl *card;
    s32 result;

    card = &lbl_80641C60[chan];
    card->cmd[0] = 0xF1;
    card->cmd[1] = (u8)((addr >> 17) & 0x7F);
    card->cmd[2] = (u8)((addr >> 9) & 0xFF);
    card->cmdlen = 3;
    card->mode = -1;
    card->retry = 3;

    result = fn_8021CD04(chan, 0, callback);
    if (result == -1) {
        result = 0;
    } else if (result >= 0) {
        if (!fn_80206AC8(chan, card->cmd, card->cmdlen, 1)) {
            card->exiCallback = 0;
            result = -3;
        } else {
            result = 0;
        }
        EXIDeselect(chan);
        EXIUnlock(chan);
    }
    return result;
}
