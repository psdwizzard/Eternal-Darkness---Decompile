/* __CARDAccess: check whether a directory entry belongs to the current disc. */
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

extern DVDDiskID lbl_80641E80; /* __CARDDiskNone */
extern int fn_800F98EC(const void *a, const void *b, unsigned long n); /* memcmp */

s32 fn_80221498(CARDControl *card, CARDDir *ent)
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

