/* CARDReadAsync: CARDReadAsync (SDK CARDRead.c). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct CARDDir {
    u8 data[0x40];
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
    u8 reserved12[0xBE];
    CARDCallback apiCallback;
} CARDControl;

#define CARD_SEG_SIZE 512
#define OFFSET(n, a) (((u32)(n)) & ((a) - 1))

extern s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard);
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);
extern CARDDir *__CARDGetDirBlock(CARDControl *card);
extern s32 __CARDAccess(CARDControl *card, CARDDir *ent);
extern s32 __CARDIsPublic(CARDDir *ent);
extern void DCInvalidateRange(void *addr, u32 nBytes);
extern void __CARDDefaultApiCallback(s32 channel, s32 result);
extern void ReadCallback(s32 channel, s32 result);
extern s32 __CARDRead(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback);

s32 CARDReadAsync(CARDFileInfo *fileInfo, void *buf, s32 length, s32 offset, CARDCallback callback)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;

    if (OFFSET(offset, CARD_SEG_SIZE) != 0 || OFFSET(length, CARD_SEG_SIZE) != 0) {
        return -128;
    }

    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDAccess(card, ent);
    if (result == -10) {
        result = __CARDIsPublic(ent);
    }
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    DCInvalidateRange(buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;

    offset = (s32)OFFSET(fileInfo->offset, card->sectorSize);
    length = (length < card->sectorSize - offset) ? length : card->sectorSize - offset;
    result = __CARDRead(fileInfo->chan, card->sectorSize * fileInfo->iBlock + offset, length, buf,
                         ReadCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
