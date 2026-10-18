/* __CARDSeek: __CARDSeek (SDK CARDRead.c). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 reserved06[2];
    u8 fileName[32];
    u8 reserved28[0xE];
    u16 startBlock;
    u16 length;
    u8 reserved3A[6];
} CARDDir;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 __padding;
} CARDFileInfo;

typedef struct CARDControl {
    u8 reserved00[0xC];
    s32 sectorSize;
    u16 cBlock;
    u8 reserved12[0xAE];
    CARDFileInfo *fileInfo;
} CARDControl;

#define CARD_NUM_SYSTEM_BLOCK 5
#define CARDIsValidBlockNo(card, iBlock) \
    (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)
#define TRUNC(n, a) (((u32)(n)) & ~((a) - 1))

extern s32 __CARDGetControlBlock(s32 chan, CARDControl **card);
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);
extern CARDDir *__CARDGetDirBlock(CARDControl *card);
extern u16 *__CARDGetFatBlock(CARDControl *card);

s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    u16 *fat;

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }

    if (!CARDIsValidBlockNo(card, fileInfo->iBlock) ||
        card->cBlock * card->sectorSize <= fileInfo->offset) {
        return __CARDPutControlBlock(card, -128);
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    if (ent->length * card->sectorSize <= offset ||
        ent->length * card->sectorSize < offset + length) {
        return __CARDPutControlBlock(card, -11);
    }

    card->fileInfo = fileInfo;
    fileInfo->length = length;
    if (offset < fileInfo->offset) {
        fileInfo->offset = 0;
        fileInfo->iBlock = ent->startBlock;
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
            return __CARDPutControlBlock(card, -6);
        }
    }

    fat = __CARDGetFatBlock(card);
    while (fileInfo->offset < TRUNC(offset, card->sectorSize)) {
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
            return __CARDPutControlBlock(card, -6);
        }
    }

    fileInfo->offset = offset;
    *pcard = card;
    return 0;
}
