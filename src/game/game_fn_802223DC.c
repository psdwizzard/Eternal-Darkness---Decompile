typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct CARDDir {
    u8 reserved00[0x36];
    u16 startBlock;
    u8 reserved38[0x08];
} CARDDir;

typedef struct CARDControl {
    u8 reserved00[0xBE];
    u16 freeNo;
    u8 reservedC0[0x10];
    CARDCallback apiCallback;
} CARDControl;

extern s32 __CARDGetControlBlock(s32 channel, CARDControl **card);
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);
extern CARDDir *__CARDGetDirBlock(CARDControl *card);
extern s32 __CARDUpdateDir(s32 channel, CARDCallback callback);
extern s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *fileNo);
extern s32 __CARDIsOpened(CARDControl *card, s32 fileNo);
extern void *memset(void *dst, s32 value, u32 size);
extern void __CARDDefaultApiCallback(s32 channel, s32 result);
extern void DeleteCallback(s32 channel, s32 result);

s32 CARDDeleteAsync(s32 channel, const char *fileName, CARDCallback callback)
{
    CARDControl *card;
    s32 fileNo;
    s32 result;
    CARDDir *dir;

    result = __CARDGetControlBlock(channel, &card);
    if (result < 0) {
        return result;
    }

    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    if (__CARDIsOpened(card, fileNo) != 0) {
        return __CARDPutControlBlock(card, -1);
    }

    dir = __CARDGetDirBlock(card) + fileNo;
    card->freeNo = dir->startBlock;
    memset(dir, 0xFF, 0x40);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    result = __CARDUpdateDir(channel, DeleteCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
