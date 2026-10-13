typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct DspTask DspTask;
struct DspTask {
    u8 pad00[0x30];
};

typedef struct Channel {
    u8 pad00[0x2c];
    u32 state;
    u8 pad30[0x50];
    u32 packet;
    u8 pad84[0x8c];
} Channel;

extern Channel lbl_80641C60[];
extern s32 fn_8021D8F0(void);
extern s32 fn_8021D7AC(s32, u32, u32 *, s32, s32);
extern s32 fn_8021C788(s32, u8 *);
extern s32 fn_802070C4(s32);
extern void EXIUnlock(s32);
extern void fn_802207C0(s32, s32);

#define LEFT_FEEDBACK(x) (~((x) ^ ((x) << 7) ^ ((x) << 15) ^ ((x) << 23)))
#define LEFT_STEP(x) ((x) = ((x) << 1) | ((LEFT_FEEDBACK(x) >> 30) & 2))

void fn_8021E57C(DspTask *task)
{
    Channel *channel;
    s32 device;
    u32 seed, key, bit_count, i;
    u32 transfer[1];
    u8 response;
    s32 result;

    device = 0;
    channel = &lbl_80641C60[0];
    if ((u8 *)channel + 0x30 != (u8 *)task) {
        channel = (Channel *)((u8 *)lbl_80641C60 + 0x110);
        device = 1;
        if ((u8 *)lbl_80641C60 + 0x140 != (u8 *)task)
            device = 2;
    }

    key = *(u32 *)(((channel->packet + 0x2f) & 0xffffffe0) + 0x20);
    seed = channel->state;
    result = fn_8021D8F0();
    if (fn_8021D7AC(device, (key ^ seed) & 0xffff0000,
                    transfer, result, 1) < 0) {
        EXIUnlock(device);
        fn_802207C0(device, -3);
        return;
    }

    bit_count = (result + *(u32 *)((u8 *)channel + 0x14) + 4) * 8 + 1;
    seed = channel->state;
    for (i = 0; i < bit_count; ++i)
        LEFT_STEP(seed);
    channel->state = seed | (LEFT_FEEDBACK(seed) >> 31);

    result = fn_8021D8F0();
    seed = channel->state;
    if (fn_8021D7AC(device, ((key << 16) ^ seed) & 0xffff0000,
                    transfer, result, 1) < 0) {
        EXIUnlock(device);
        fn_802207C0(device, -3);
        return;
    }

    result = fn_8021C788(device, &response);
    if (fn_802070C4(device) == 0) {
        EXIUnlock(device);
        fn_802207C0(device, -3);
        return;
    }
    if (result == 0 && !(response & 0x40)) {
        EXIUnlock(device);
        result = -5;
    }
    fn_802207C0(device, result);
}
