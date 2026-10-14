/* fn_8021D3D8: CARDGetResultCode. */
typedef unsigned char u8;
typedef signed int s32;

typedef struct CARDControl {
    s32 attached;
    s32 result;
    u8 reserved08[0x110 - 0x08];
} CARDControl;

extern CARDControl lbl_80641C60[];

s32 fn_8021D3D8(s32 channel)
{
    CARDControl *card;

    if (channel < 0 || channel >= 2) {
        return -128;
    }
    card = &lbl_80641C60[channel];
    return card->result;
}
