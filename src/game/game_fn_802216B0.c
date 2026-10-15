/* fn_802216B0: CARDOpen (SDK CARDOpen.c), with __CARDGetFileNo and
 * __CARDAccess inlined. */
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

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 __padding;
} CARDFileInfo;

typedef struct CARDControl {
    BOOL attached;
    u8 reserved04[0xC];
    u16 cBlock;
    u8 reserved12[0xFA];
    DVDDiskID *diskID;
} CARDControl;

#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_MAX_FILE 127
#define CARDIsValidBlockNo(card, iBlock) \
    (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)

extern DVDDiskID lbl_80641E80; /* __CARDDiskNone */

extern int fn_800F98EC(const void *a, const void *b, unsigned long n); /* memcmp */
extern s32 fn_8021D2BC(s32 chan, CARDControl **card);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern CARDDir *fn_8021EF3C(CARDControl *card);
extern BOOL fn_80221430(CARDDir *ent, const char *fileName); /* __CARDCompareFileName */

static inline s32 __CARDAccess(CARDControl *card, CARDDir *ent)
{
    if (ent->gameName[0] == 0xFF) {
        return -4;
    }

    if (card->diskID == &lbl_80641E80 ||
        (fn_800F98EC(ent->gameName, card->diskID->gameName, 4) == 0 &&
         fn_800F98EC(ent->company, card->diskID->company, 2) == 0)) {
        return 0;
    }

    return -10;
}

static inline s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo)
{
    CARDDir *dir;
    CARDDir *ent;
    s32 fileNo;

    if (!card->attached) {
        return -3;
    }

    dir = fn_8021EF3C(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        ent = &dir[fileNo];
        if (__CARDAccess(card, ent) < 0) {
            continue;
        }
        if (fn_80221430(ent, fileName)) {
            *pfileNo = fileNo;
            return 0;
        }
    }

    return -4;
}

s32 fn_802216B0(s32 chan, const char *fileName, CARDFileInfo *fileInfo)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    s32 fileNo;

    fileInfo->chan = -1;
    result = fn_8021D2BC(chan, &card);
    if (result < 0) {
        return result;
    }

    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (0 <= result) {
        dir = fn_8021EF3C(card);
        ent = &dir[fileNo];
        if (!CARDIsValidBlockNo(card, ent->startBlock)) {
            result = -6;
        } else {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }

    return fn_8021D374(card, result);
}
