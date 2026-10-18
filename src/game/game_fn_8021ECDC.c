/* __CARDAllocBlock (0x8021ECDC, 280 bytes): __CARDAllocBlock. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad04[0xc];
    u16 cBlock;
    u8 pad12[0x76];
    void *currentFat;
    u8 pad8C[0x32];
    u16 startBlock;
    u8 padC0[0x50];
} CARDControl;

extern CARDControl __CARDBlock[];
extern s32 __CARDUpdateFatBlock(s32, void *, CARDCallback);

static inline void *__CARDGetFatBlock(CARDControl *card)
{
    return card->currentFat;
}

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback)
{
    u16 *fat;
    CARDControl *card;
    u16 iBlock;
    u16 startBlock;
    u16 prevBlock;
    u16 count;

    card = &__CARDBlock[chan];
    if (!card->attached)
        return -3;

    fat = __CARDGetFatBlock(card);
    if (fat[3] < cBlock)
        return -9;

    fat[3] -= cBlock;
    startBlock = 0xFFFF;
    iBlock = fat[4];
    count = 0;
    while (0 < cBlock) {
        if (card->cBlock - 5 < ++count)
            return -6;

        iBlock++;
        if (!(5 <= iBlock && iBlock < card->cBlock))
            iBlock = 5;

        if (fat[iBlock] == 0) {
            if (startBlock == 0xFFFF) {
                startBlock = iBlock;
            } else {
                fat[prevBlock] = iBlock;
            }
            prevBlock = iBlock;
            fat[iBlock] = 0xFFFF;
            --cBlock;
        }
    }
    fat[4] = iBlock;
    card->startBlock = startBlock;

    return __CARDUpdateFatBlock(chan, fat, callback);
}
