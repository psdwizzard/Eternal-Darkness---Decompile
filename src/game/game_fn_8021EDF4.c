/* Free a chain of memory card blocks in the FAT and write the table back. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    s32 attached;
    u8 reserved04[0xC];
    u16 blockCount;
    u8 reserved12[0x76];
    u16 *currentFat;
    u8 reserved8C[0x84];
} CardControl;

extern CardControl __CARDBlock[];
extern s32 __CARDUpdateFatBlock(s32 channel, u16 *fat, CardCallback callback);

static inline CardControl *GetCard(s32 channel)
{
    return &__CARDBlock[channel];
}

static inline u16 *GetFatBlock(CardControl *card)
{
    return card->currentFat;
}

s32 __CARDFreeBlock(s32 channel, u16 block, CardCallback callback)
{
    CardControl *card;
    u16 *fat;
    u16 next;

    card = GetCard(channel);
    if (!card->attached) {
        return -3;
    }

    fat = GetFatBlock(card);
    while (block != 0xFFFF) {
        if (block < 5 || block >= card->blockCount) {
            return -6;
        }
        next = fat[block];
        fat[block] = 0;
        block = next;
        ++fat[3];
    }
    return __CARDUpdateFatBlock(channel, fat, callback);
}
