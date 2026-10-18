/* Update the memory card directory checksum and begin erasing its sector. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    s32 attached;
    u8 reserved04[8];
    s32 sectorSize;
    u8 reserved10[0x70];
    void *workArea;
    void *currentDir;
    u8 reserved88[0x50];
    CardCallback eraseCallback;
    u8 reservedDC[0x34];
} CardControl;

typedef struct CardDirCheck {
    u8 reserved00[0x3A];
    s16 checkCode;
    u16 checksum;
    u16 checksumInv;
} CardDirCheck;

extern CardControl __CARDBlock[];
extern void __CARDCheckSum(u16 *data, s32 length, u16 *checksum, u16 *checksumInv);
extern void DCStoreRange(void *address, u32 length);
extern s32 __CARDEraseSector(s32 channel, u32 address, CardCallback callback);
extern void fn_8021F014(s32 channel, s32 result);

static inline CardDirCheck *GetDirectoryBlock(CardControl *card)
{
    CardDirCheck *dir = card->currentDir;
    return dir;
}

s32 __CARDUpdateDir(s32 channel, CardCallback callback)
{
    CardDirCheck *dir;
    CardControl *card;
    CardDirCheck *check;
    u32 address;

    card = &__CARDBlock[channel];
    if (!card->attached) {
        return -3;
    }
    dir = GetDirectoryBlock(card);
    check = &dir[127];
    ++check->checkCode;
    __CARDCheckSum((u16 *)dir, 0x1FFC, &check->checksum, &check->checksumInv);
    DCStoreRange(dir, 0x2000);
    card->eraseCallback = callback;
    address = ((u32)dir - (u32)card->workArea) / 0x2000 * card->sectorSize;
    return __CARDEraseSector(channel, address, fn_8021F014);
}
