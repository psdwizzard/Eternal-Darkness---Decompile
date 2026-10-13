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

extern s32 fn_8021D2BC(s32 channel, CARDControl **card);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern s32 fn_8021EF3C(CARDControl *card);
extern s32 fn_8021F0DC(s32 channel, CARDCallback callback, CARDControl *card);
extern s32 fn_80221560(CARDControl *card, const char *fileName, s32 *fileNo);
extern s32 fn_8022187C(CARDControl *card, s32 fileNo);
extern void *memset(void *dst, s32 value, u32 size);
extern void fn_8021C374(s32 channel, s32 result);
extern void fn_80222338(s32 channel, s32 result);

s32 fn_802223DC(s32 channel, const char *fileName, CARDCallback callback)
{
    CARDControl *card;
    s32 fileNo;
    s32 result;
    CARDDir *dir;

    result = fn_8021D2BC(channel, &card);
    if (result < 0) {
        return result;
    }

    result = fn_80221560(card, fileName, &fileNo);
    if (result < 0) {
        return fn_8021D374(card, result);
    }
    if (fn_8022187C(card, fileNo) != 0) {
        return fn_8021D374(card, -1);
    }

    dir = (CARDDir *)fn_8021EF3C(card) + fileNo;
    card->freeNo = dir->startBlock;
    memset(dir, 0xFF, 0x40);
    card->apiCallback = callback ? callback : fn_8021C374;
    result = fn_8021F0DC(channel, fn_80222338, card);
    if (result < 0) {
        fn_8021D374(card, result);
    }
    return result;
}
