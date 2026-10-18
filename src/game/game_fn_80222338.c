/* Completion callback for deleting a CARD file: frees the file's blocks
 * and reports the result to the user callback. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct CARDControl {
    u8 reserved00[0xBE];
    u16 startBlock;
    u8 reservedC0[0x10];
    CARDCallback callback;
    u8 reservedD4[0x3C];
} CARDControl;

extern CARDControl __CARDBlock[];
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);
extern s32 __CARDFreeBlock(s32 channel, u16 block, CARDCallback callback);

void DeleteCallback(s32 channel, s32 result)
{
    CARDControl *card = &__CARDBlock[channel];
    CARDCallback callback;

    callback = card->callback;
    card->callback = 0;
    if (result < 0) {
        goto error;
    }
    result = __CARDFreeBlock(channel, card->startBlock, callback);
    if (result < 0) {
        goto error;
    }
    return;

error:
    __CARDPutControlBlock(card, result);
    if (callback) {
        callback(channel, result);
    }
}
