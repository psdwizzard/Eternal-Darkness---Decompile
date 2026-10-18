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

extern CardControl __CARDBlock[];
extern s32 DoMount(s32 channel);
extern s32 __CARDVerify(CardControl *control);
extern void DoUnmount(s32 channel, s32 result);
extern s32 __CARDPutControlBlock(CardControl *control, s32 result);

void __CARDMountCallback(s32 channel, s32 result)
{
    CardControl *control = &__CARDBlock[channel];
    CardCallback callback;

    switch (result) {
    case 0:
        if (++control->mountStep < 7) {
            result = DoMount(channel);
            if (result >= 0) {
                return;
            }
        } else {
            result = __CARDVerify(control);
        }
        break;
    case 1:
        result = DoMount(channel);
        if (result >= 0) {
            return;
        }
        break;
    case -3:
    case -5:
        DoUnmount(channel, result);
        break;
    }

    callback = control->apiCallback;
    control->apiCallback = 0;
    __CARDPutControlBlock(control, result);
    callback(channel, result);
}
