/* fn_802219B4: CARDCreateAsync (SDK CARDCreate.c). */
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
extern char *fn_800FD3C8(char *dst, const char *src, unsigned long n); /* strncpy */
extern s32 fn_8021D2BC(s32 chan, CARDControl **card);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern void fn_8021C374(s32 chan, s32 result);
extern CARDDir *fn_8021EF3C(CARDControl *card);
extern u16 *fn_8021EB38(CARDControl *card);
extern s32 fn_80221430(CARDDir *ent, const char *fileName);
extern s32 fn_8021ECDC(s32 chan, u32 cBlock, CARDCallback callback);
extern void fn_80221884(s32 chan, s32 result);

s32 fn_802219B4(s32 chan, const char *fileName, u32 size, CARDFileInfo *fileInfo,
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

    result = fn_8021D2BC(chan, &card);
    if (result < 0) {
        return result;
    }

    if (size <= 0 || (size % card->sectorSize) != 0) {
        return -128;
    }

    freeNo = (u16)-1;
    dir = fn_8021EF3C(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xFF) {
            if (freeNo == (u16)-1) {
                freeNo = fileNo;
            }
        } else if (fn_800F98EC(ent->gameName, card->diskID->gameName, sizeof(ent->gameName)) == 0
                   && fn_800F98EC(ent->company, card->diskID->company, sizeof(ent->company)) == 0
                   && fn_80221430(ent, fileName)) {
            return fn_8021D374(card, -7);
        }
    }
    if (freeNo == (u16)-1) {
        return fn_8021D374(card, -8);
    }

    fat = fn_8021EB38(card);
    if (card->sectorSize * fat[3] < size) {
        return fn_8021D374(card, -9);
    }

    card->apiCallback = callback ? callback : fn_8021C374;
    card->freeNo = freeNo;
    ent = &dir[freeNo];
    ent->length = (u16)(size / card->sectorSize);
    fn_800FD3C8((char *)ent->fileName, fileName, 32);

    card->fileInfo = fileInfo;
    fileInfo->chan = chan;
    fileInfo->fileNo = freeNo;

    result = fn_8021ECDC(chan, size / card->sectorSize, fn_80221884);
    if (result < 0) {
        return fn_8021D374(card, result);
    }
    return result;
}
