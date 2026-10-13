/* fn_8021D2BC: __CARDGetControlBlock. */
typedef unsigned char u8;
typedef signed int s32;
typedef int BOOL;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u8 reserved08[0xD0 - 0x08];
    CARDCallback apiCallback;
    u8 reservedD4[0x10C - 0xD4];
    const void *diskID;
} CARDControl;

extern CARDControl lbl_80641C60[];
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

s32 fn_8021D2BC(s32 chan, CARDControl **outCard)
{
    s32 result;
    CARDControl *card;
    BOOL enabled;

    card = &lbl_80641C60[chan];
    if (chan < 0 || chan >= 2 || card->diskID == 0) {
        return -128;
    }

    enabled = OSDisableInterrupts();
    if (!card->attached) {
        result = -3;
    } else if (card->result == -1) {
        result = -1;
    } else {
        card->result = -1;
        result = 0;
        card->apiCallback = 0;
        *outCard = card;
    }
    OSRestoreInterrupts(enabled);
    return result;
}
