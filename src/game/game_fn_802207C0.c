typedef unsigned char u8;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    u8 reserved00[0x24];
    s32 mountStep;
    u8 reserved28[0xA8];
    CardCallback apiCallback;
    u8 reservedD4[0x3C];
} CardControl;

extern CardControl lbl_80641C60[];
extern s32 fn_802203B0(s32 channel);
extern s32 fn_8021FA98(CardControl *control);
extern void fn_80220AB0(s32 channel, s32 result);
extern s32 fn_8021D374(CardControl *control, s32 result);

void fn_802207C0(s32 channel, s32 result)
{
    CardControl *control = &lbl_80641C60[channel];
    CardCallback callback;

    switch (result) {
    case 0:
        if (++control->mountStep < 7) {
            result = fn_802203B0(channel);
            if (result >= 0) {
                return;
            }
        } else {
            result = fn_8021FA98(control);
        }
        break;
    case 1:
        result = fn_802203B0(channel);
        if (result >= 0) {
            return;
        }
        break;
    case -3:
    case -5:
        fn_80220AB0(channel, result);
        break;
    }

    callback = control->apiCallback;
    control->apiCallback = 0;
    fn_8021D374(control, result);
    callback(channel, result);
}
