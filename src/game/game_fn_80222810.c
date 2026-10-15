/* CARDSetStatusAsync: update the directory entry and its image layout. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long OSTime;
typedef void (*CardCallback)(s32 channel, s32 result);

/* Keep these views identical to the definitions in game_fn_802224EC.c.
 * Layout includes every output written by that helper. */
typedef struct Desc {
    u8 pad0[0x7];
    u8 flags;
    u8 pad8[0x2C - 0x8];
    u32 base;
    u16 chanBits;
} Desc;

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
typedef struct CARDControl CARDControl;

extern s32 fn_8021D2BC(s32 channel, CARDControl **outCard);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern CARDDir *fn_8021EF3C(CARDControl *card);
extern s32 fn_80221498(CARDControl *card, CARDDir *entry);
extern void fn_802224EC(Desc *desc, Layout *out);
extern s32 fn_8021F0DC(s32 channel, CardCallback callback);
extern OSTime OSGetTime(void);
extern long long fn_800F5ECC(long long numerator, long long denominator);

s32 fn_80222810(s32 channel, s32 fileNo, Layout *status, CardCallback callback)
{
    CARDControl *card;
    CARDDir *entry;
    s32 result;
    u32 ticksPerSecond;

    /* The helper leaves the input icon address (0x30) and comment address
     * (0x38) unnamed in its Layout view. */
    if (fileNo < 0 || fileNo >= 127 ||
        ((*(u32 *)&status->pad2F[1]) != 0xFFFFFFFF && (*(u32 *)&status->pad2F[1]) >= 0x200) ||
        ((*(u32 *)status->pad38) != 0xFFFFFFFF && ((*(u32 *)status->pad38) & 0x1FFF) > 0x1FC0)) {
        return -128;
    }
    result = fn_8021D2BC(channel, &card);
    if (result < 0) {
        return result;
    }
    entry = fn_8021EF3C(card) + fileNo;
    result = fn_80221498(card, entry);
    if (result < 0) {
        return fn_8021D374(card, result);
    }
    /* Directory fields: banner format at 0x07, icon address at 0x2C,
     * icon format at 0x30, animation speed at 0x32, comment at 0x3C. */
    entry->reserved06[1] = status->unk2E;
    *(u32 *)&entry->reserved28[4] = *(u32 *)&status->pad2F[1];
    *(u16 *)&entry->reserved28[8] = status->unk34;
    *(u16 *)&entry->reserved28[10] = status->unk36;
    *(u32 *)&entry->reserved3A[2] = *(u32 *)status->pad38;
    fn_802224EC((Desc *)entry, status);
    if (*(u32 *)&entry->reserved28[4] == 0xFFFFFFFF) {
        *(u16 *)&entry->reserved28[10] = (*(u16 *)&entry->reserved28[10] & ~3) | 1;
    }
    /* OS time is unsigned; the SDK uses signed 64-bit division here. */
    ticksPerSecond = *(volatile u32 *)0x800000F8 >> 2;
    *(u32 *)entry->reserved28 = (u32)fn_800F5ECC((long long)OSGetTime(), (long long)ticksPerSecond);
    result = fn_8021F0DC(channel, callback);
    if (result < 0) {
        fn_8021D374(card, result);
    }
    return result;
}
