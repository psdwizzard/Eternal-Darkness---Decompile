/* __CARDIsPublic: check whether an existing directory entry allows public reads. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 padding0;
    u8 bannerFormat;
    u8 fileName[32];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 padding1[2];
    u32 commentAddr;
} CARDDir;

s32 fn_80221530(CARDDir *ent)
{
    if (ent->gameName[0] == 0xFF) {
        return -4;
    }

    if (ent->permission & 4) {
        return 0;
    }

    return -10;
}
