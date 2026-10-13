/* Continuation of an asynchronous CARD read. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef u64 OSTime;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 padding;
} CARDFileInfo;

typedef struct CARDDir {
    u8 reserved00[0x28];
    u32 time;
    u8 reserved2C[0x14];
} CARDDir;

typedef struct CARDControl {
    u8 reserved00[0xC];
    s32 sectorSize;
    u16 cBlock;
    u8 reserved12[0xAE];
    CARDFileInfo *fileInfo;
    u8 reservedC4[0xC];
    CARDCallback callback;
    u8 reservedD4[0x3C];
} CARDControl;

extern CARDControl lbl_80641C60[];
extern CARDDir *fn_8021EF3C(CARDControl *card);
extern u16 *fn_8021EB38(CARDControl *card);
extern s32 fn_8021F0DC(s32 channel, CARDCallback callback);
extern s32 fn_8021D108(s32 channel, u32 address, CARDCallback callback);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern void fn_80222174(s32 channel, s32 result);
extern OSTime OSGetTime(void);
extern s64 fn_800F5ECC(s64 dividend, s64 divisor);

void fn_80222004(s32 channel, s32 result)
{
    CARDControl *card = &lbl_80641C60[channel];
    CARDFileInfo *fileInfo;
    CARDCallback callback;

    if (result >= 0) {
        fileInfo = card->fileInfo;
        if (fileInfo->length < 0) {
            result = -14;
            goto error;
        }

        fileInfo->length -= card->sectorSize;
        if (fileInfo->length <= 0) {
            u32 ticksPerSecond;
            CARDDir *entry;
            entry = &fn_8021EF3C(card)[fileInfo->fileNo];
            ticksPerSecond = *(u32 *)0x800000F8 >> 2;
            entry->time = (u32)fn_800F5ECC((s64)OSGetTime(), (s64)ticksPerSecond);
            callback = card->callback;
            card->callback = 0;
            result = fn_8021F0DC(channel, callback);
        } else {
            u16 *fat = fn_8021EB38(card);
            fileInfo->offset += card->sectorSize;
            fileInfo->iBlock = fat[fileInfo->iBlock];
            if (fileInfo->iBlock < 5 || fileInfo->iBlock >= card->cBlock) {
                result = -6;
                goto error;
            }
            result = fn_8021D108(channel, card->sectorSize * fileInfo->iBlock,
                                  fn_80222174);
        }
        if (result >= 0) {
            return;
        }
    }

error:
    callback = card->callback;
    card->callback = 0;
    fn_8021D374(card, result);
    callback(channel, result);
}
