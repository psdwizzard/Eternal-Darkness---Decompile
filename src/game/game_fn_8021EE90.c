/* Update the memory card allocation table checksum and erase its sector. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    u8 reserved00[0xC];
    s32 sectorSize;
    u8 reserved10[0x70];
    void *workArea;
    u8 reserved84[0x54];
    CardCallback eraseCallback;
    u8 reservedDC[0x34];
} CardControl;

extern CardControl lbl_80641C60[];
extern void fn_8021F1A0(u16 *data, s32 length, u16 *checksum, u16 *checksumInv);
extern void fn_8020B774(void *address, u32 length);
extern s32 fn_8021D108(s32 channel, u32 address, CardCallback callback);
extern void fn_8021EC14(s32 channel, s32 result);

s32 fn_8021EE90(s32 channel, u16 *fat, CardCallback callback)
{
    CardControl *card;
    u32 address;

    ++fat[2];
    card = &lbl_80641C60[channel];
    fn_8021F1A0(fat + 2, 0x1FFC, fat, fat + 1);
    fn_8020B774(fat, 0x2000);
    card->eraseCallback = callback;
    address = ((u32)fat - (u32)card->workArea) / 0x2000 * card->sectorSize;
    return fn_8021D108(channel, address, fn_8021EC14);
}
