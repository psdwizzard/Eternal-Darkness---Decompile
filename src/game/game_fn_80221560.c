/* __CARDGetFileNo: __CARDGetFileNo (SDK CARDOpen.c), with __CARDAccess and
 * __CARDCompareFileName inlined. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

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

typedef struct CARDControl {
    BOOL attached;
    u8 reserved04[0xC];
    u16 cBlock;
    u8 reserved12[0xFA];
    DVDDiskID *diskID;
} CARDControl;

#define CARD_MAX_FILE 127
#define CARD_FILENAME_MAX 32

extern DVDDiskID __CARDDiskNone; /* __CARDDiskNone */

extern int fn_800F98EC(const void *a, const void *b, unsigned long n); /* memcmp */
extern CARDDir *__CARDGetDirBlock(CARDControl *card);

static inline s32 __CARDAccess(CARDControl *card, CARDDir *ent)
{
    if (ent->gameName[0] == 0xFF) {
        return -4;
    }

    if (card->diskID == &__CARDDiskNone ||
        (fn_800F98EC(ent->gameName, card->diskID->gameName, 4) == 0 &&
         fn_800F98EC(ent->company, card->diskID->company, 2) == 0)) {
        return 0;
    }

    return -10;
}

static inline BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName)
{
    char *entName;
    char c1;
    char c2;
    int n;

    entName = (char *)ent->fileName;
    n = CARD_FILENAME_MAX;
    while (0 <= --n) {
        if ((c1 = *entName++) != (c2 = *fileName++)) {
            return 0;
        } else if (c2 == '\0') {
            return 1;
        }
    }

    if (*fileName == '\0') {
        return 1;
    }

    return 0;
}

s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo)
{
    CARDDir *dir;
    CARDDir *ent;
    s32 fileNo;
    s32 result;

    if (!card->attached) {
        return -3;
    }

    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        ent = &dir[fileNo];
        result = __CARDAccess(card, ent);
        if (result < 0) {
            continue;
        }
        if (__CARDCompareFileName(ent, fileName)) {
            *pfileNo = fileNo;
            return 0;
        }
    }

    return -4;
}
