/* fn_80221BD4: __CARDSeek (SDK CARDRead.c). */
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

extern s32 fn_8021D2BC(s32 chan, CARDControl **card);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern CARDDir *fn_8021EF3C(CARDControl *card);
extern u16 *fn_8021EB38(CARDControl *card);

s32 fn_80221BD4(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    u16 *fat;

    result = fn_8021D2BC(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }

    if (!CARDIsValidBlockNo(card, fileInfo->iBlock) ||
        card->cBlock * card->sectorSize <= fileInfo->offset) {
        return fn_8021D374(card, -128);
    }

    dir = fn_8021EF3C(card);
    ent = &dir[fileInfo->fileNo];
    if (ent->length * card->sectorSize <= offset ||
        ent->length * card->sectorSize < offset + length) {
        return fn_8021D374(card, -11);
    }

    card->fileInfo = fileInfo;
    fileInfo->length = length;
    if (offset < fileInfo->offset) {
        fileInfo->offset = 0;
        fileInfo->iBlock = ent->startBlock;
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
            return fn_8021D374(card, -6);
        }
    }

    fat = fn_8021EB38(card);
    while (fileInfo->offset < TRUNC(offset, card->sectorSize)) {
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
            return fn_8021D374(card, -6);
        }
    }

    fileInfo->offset = offset;
    *pcard = card;
    return 0;
}
