/* Read a directory entry and expand its status fields. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Desc {
    u8 pad0[7];
    u8 flags;
    u8 pad8[0x24];
    u32 base;
    u16 chanBits;
} Desc;

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

typedef struct Layout {
    u8 pad0[0x2E];
    u8 unk2E;
    u8 pad2F[0x34 - 0x2F];
    u16 unk34;
    u16 unk36;
    u8 pad38[0x3C - 0x38];
    s32 unk3C;
    s32 unk40;
    s32 chan[8];
    s32 unk64;
    s32 unk68;
} Layout;

typedef struct CARDControl {
    u8 pad0[0xC];
    u32 sectorSize;
} CARDControl;

extern s32 fn_8021D2BC(s32 chan, CARDControl **outCard);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern CARDDir *fn_8021EF3C(CARDControl *card);
extern s32 fn_80221498();
extern s32 fn_80221530(CARDDir *entry);
extern void fn_802224EC(Desc *desc, Layout *out);
extern void *memcpy(void *dst, const void *src, unsigned long size);

s32 fn_802226E4(s32 chan, s32 fileNo, Layout *stat)
{
    CARDControl *card;
    CARDDir *entry;
    s32 result;

    if (fileNo < 0 || fileNo >= 0x7F) {
        return -128;
    }
    result = fn_8021D2BC(chan, &card);
    if (result < 0) {
        return result;
    }
    entry = &fn_8021EF3C(card)[fileNo];
    result = fn_80221498(card, entry);
    if (result == -10) {
        result = fn_80221530(entry);
    }
    if (result >= 0) {
        memcpy(stat->pad0 + 0x28, entry, 4);
        memcpy(stat->pad0 + 0x2C, (u8 *)entry + 4, 2);
        *(u32 *)(stat->pad0 + 0x20) = entry->length * card->sectorSize;
        memcpy(stat->pad0, (u8 *)entry + 8, 32);
        *(u32 *)(stat->pad0 + 0x24) = *(u32 *)((u8 *)entry + 0x28);
        stat->unk2E = entry->bannerFormat;
        *(u32 *)((u8 *)stat + 0x30) = entry->iconAddr;
        stat->unk34 = entry->iconFormat;
        stat->unk36 = entry->iconSpeed;
        *(u32 *)stat->pad38 = entry->commentAddr;
        fn_802224EC((Desc *)entry, stat);
    }
    return fn_8021D374(card, result);
}
