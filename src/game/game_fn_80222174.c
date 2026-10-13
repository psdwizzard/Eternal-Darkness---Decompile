/* Continue an asynchronous CARD write after erasing a sector. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 padding;
} CARDFileInfo;

typedef struct CARDControl {
    u8 reserved00[0xC];
    s32 sectorSize;
    u8 reserved10[0xA4];
    void *buffer;
    u8 reservedB8[8];
    CARDFileInfo *fileInfo;
    u8 reservedC4[0xC];
    CARDCallback callback;
    u8 reservedD4[0x3C];
} CARDControl;

extern CARDControl lbl_80641C60[];
extern s32 fn_8021EABC(s32 channel, u32 address, s32 length, void *buffer,
                       CARDCallback callback);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern void fn_80222004(s32 channel, s32 result);

void fn_80222174(s32 channel, s32 result)
{
    CARDControl *card = &lbl_80641C60[channel];
    CARDCallback callback;

    if (result >= 0) {
        result = fn_8021EABC(channel, card->sectorSize * card->fileInfo->iBlock,
                             card->sectorSize, card->buffer, fn_80222004);
        if (result >= 0) {
            return;
        }
    }

    callback = card->callback;
    card->callback = 0;
    fn_8021D374(card, result);
    callback(channel, result);
}
