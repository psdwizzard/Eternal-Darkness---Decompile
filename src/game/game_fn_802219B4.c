/* CARDCreateAsync: CARDCreateAsync (SDK CARDCreate.c). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef void (*CARDCallback)(s32 chan, s32 result);

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
} DVDDiskID;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 reserved06[2];
    u8 fileName[32];
    u8 reserved28[0x10];
    u16 length;
    u8 reserved3A[6];
} CARDDir;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
} CARDFileInfo;

typedef struct CARDControl {
    u8 reserved00[0xC];
    u32 sectorSize;
    u8 reserved10[0xAC];
    u16 freeNo;
    u8 reservedBE[2];
    CARDFileInfo *fileInfo;
    u8 reservedC4[0xC];
    CARDCallback apiCallback;
    u8 reservedD4[0x38];
    DVDDiskID *diskID;
} CARDControl;

extern unsigned long strlen(const char *s);
extern int fn_800F98EC(const void *a, const void *b, unsigned long n); /* memcmp */
extern char *strncpy(char *dst, const char *src, unsigned long n); /* strncpy */
extern s32 __CARDGetControlBlock(s32 chan, CARDControl **card);
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern CARDDir *__CARDGetDirBlock(CARDControl *card);
extern u16 *__CARDGetFatBlock(CARDControl *card);
extern s32 __CARDCompareFileName(CARDDir *ent, const char *fileName);
extern s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
extern void CreateCallbackFat(s32 chan, s32 result);

s32 CARDCreateAsync(s32 chan, const char *fileName, u32 size, CARDFileInfo *fileInfo,
                CARDCallback callback)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    u16 fileNo;
    u16 freeNo;
    u16 *fat;

    if (strlen(fileName) > (u32)32) {
        return -12;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    if (size <= 0 || (size % card->sectorSize) != 0) {
        return -128;
    }

    freeNo = (u16)-1;
    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xFF) {
            if (freeNo == (u16)-1) {
                freeNo = fileNo;
            }
        } else if (fn_800F98EC(ent->gameName, card->diskID->gameName, sizeof(ent->gameName)) == 0
                   && fn_800F98EC(ent->company, card->diskID->company, sizeof(ent->company)) == 0
                   && __CARDCompareFileName(ent, fileName)) {
            return __CARDPutControlBlock(card, -7);
        }
    }
    if (freeNo == (u16)-1) {
        return __CARDPutControlBlock(card, -8);
    }

    fat = __CARDGetFatBlock(card);
    if (card->sectorSize * fat[3] < size) {
        return __CARDPutControlBlock(card, -9);
    }

    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    card->freeNo = freeNo;
    ent = &dir[freeNo];
    ent->length = (u16)(size / card->sectorSize);
    strncpy((char *)ent->fileName, fileName, 32);

    card->fileInfo = fileInfo;
    fileInfo->chan = chan;
    fileInfo->fileNo = freeNo;

    result = __CARDAllocBlock(chan, size / card->sectorSize, CreateCallbackFat);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    return result;
}
