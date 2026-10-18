/* CARDGetResultCode: CARDGetResultCode. */
typedef unsigned char u8;
typedef signed int s32;

typedef struct CARDControl {
    s32 attached;
    s32 result;
    u8 reserved08[0x110 - 0x08];
} CARDControl;

extern CARDControl __CARDBlock[];

s32 CARDGetResultCode(s32 channel)
{
    CARDControl *card;

    if (channel < 0 || channel >= 2) {
        return -128;
    }
    card = &__CARDBlock[channel];
    return card->result;
}
