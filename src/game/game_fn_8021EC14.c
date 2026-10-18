/* fn_8021EC14: EraseCallback (Dolphin SDK CARDBlock.c). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CardCallback)(s32 chan, s32 result);

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0xC];
    s32 sectorSize;
    u8 pad10[0x80 - 0x10];
    void *workArea;
    u8 pad84[4];
    u16 *currentFat;
    u8 pad8C[0xD0 - 0x8C];
    CardCallback apiCallback;
    u8 padD4[4];
    CardCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CardControl;

extern CardControl __CARDBlock[];

extern s32 __CARDPutControlBlock(CardControl *card, s32 result); /* __CARDPutControlBlock */
extern s32 __CARDWrite(s32 chan, u32 addr, s32 length, void *dst,
                       CardCallback callback);         /* __CARDWrite */
extern void fn_8021EB40(s32 chan, s32 result);         /* WriteCallback */

static inline u16 *__CARDGetFatBlock(CardControl *card)
{
    u16 *fat = card->currentFat;
    return fat;
}

void fn_8021EC14(s32 chan, s32 result)
{
    CardControl *card;
    CardCallback callback;
    u16 *fat;
    u32 addr;

    card = &__CARDBlock[chan];
    if (result < 0) {
        goto error;
    }

    fat = __CARDGetFatBlock(card);
    addr = ((u32)fat - (u32)card->workArea) / 0x2000 * card->sectorSize;
    result = __CARDWrite(chan, addr, 0x2000, fat, fn_8021EB40);
    if (result < 0) {
        goto error;
    }
    return;

error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
