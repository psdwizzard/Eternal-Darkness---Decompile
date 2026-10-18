/* CARDWriteAsync: CARDWriteAsync (SDK CARDWrite.c). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*CARDCallback)(s32 chan, s32 result);

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
    u8 reserved12[0xA2];
    void *buffer;
    u8 reservedB8[0x18];
    CARDCallback apiCallback;
} CARDControl;

#define OFFSET(n, a) (((u32)(n)) & ((a) - 1))

extern void DCStoreRange(void *addr, u32 nBytes); /* DCStoreRange */
extern s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback); /* __CARDEraseSector */
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result); /* __CARDPutControlBlock */
extern CARDDir *__CARDGetDirBlock(CARDControl *card); /* __CARDGetDirBlock */
extern s32 __CARDAccess(CARDControl *card, CARDDir *ent); /* __CARDAccess */
extern s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard); /* __CARDSeek */
extern void __CARDDefaultApiCallback(s32 chan, s32 result); /* __CARDDefaultApiCallback */
extern void fn_80222174(s32 chan, s32 result); /* EraseCallback */

s32 CARDWriteAsync(CARDFileInfo *fileInfo, const void *buf, s32 length, s32 offset, CARDCallback callback)
{
    CARDControl *card;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;

    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }

    if (OFFSET(offset, card->sectorSize) != 0 || OFFSET(length, card->sectorSize) != 0) {
        return __CARDPutControlBlock(card, -128);
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    DCStoreRange((void *)buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    card->buffer = (void *)buf;
    result = __CARDEraseSector(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock, fn_80222174);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
