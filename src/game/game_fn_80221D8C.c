/* fn_80221D8C: ReadCallback (SDK CARDRead.c). */
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
    u16 cBlock;
    u8 reserved12[0xA2];
    void *buffer;
    u8 reservedB8[0x8];
    CARDFileInfo *fileInfo;
    u8 reservedC4[0xC];
    CARDCallback apiCallback;
    u8 reservedD4[0x3C];
} CARDControl;

#define CARD_NUM_SYSTEM_BLOCK 5
#define CARDIsValidBlockNo(card, iBlock) \
    (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)
#define TRUNC(n, a) (((u32)(n)) & ~((a) - 1))

extern CARDControl lbl_80641C60[];
extern u16 *fn_8021EB38(CARDControl *card);
extern s32 fn_8021D374(CARDControl *card, s32 result);
extern s32 fn_8021E97C(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback);

void fn_80221D8C(s32 chan, s32 result)
{
    CARDControl *card;
    CARDCallback callback;
    u16 *fat;
    CARDFileInfo *fileInfo;
    s32 length;

    card = &lbl_80641C60[chan];
    if (result < 0) {
        goto error;
    }

    fileInfo = card->fileInfo;
    if (fileInfo->length < 0) {
        result = -14;
        goto error;
    }

    length = (s32)TRUNC(fileInfo->offset + card->sectorSize, card->sectorSize) - fileInfo->offset;
    fileInfo->length -= length;
    if (fileInfo->length <= 0) {
        goto error;
    }

    fat = fn_8021EB38(card);
    fileInfo->offset += length;
    fileInfo->iBlock = fat[fileInfo->iBlock];
    if (!CARDIsValidBlockNo(card, fileInfo->iBlock)) {
        result = -6;
        goto error;
    }
    result = fn_8021E97C(chan, card->sectorSize * (u32)fileInfo->iBlock,
                         (fileInfo->length < card->sectorSize) ? fileInfo->length : card->sectorSize,
                         card->buffer, fn_80221D8C);
    if (result < 0) {
        goto error;
    }
    return;

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    fn_8021D374(card, result);
    callback(chan, result);
}
