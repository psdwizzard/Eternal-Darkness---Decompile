typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct DspTask DspTask;
struct DspTask {
    u8 data[0x50];
};

typedef struct Channel {
    u8 pad00[0x14];
    s32 latency;
    u8 pad18[0x14];
    u32 state;
    DspTask task;
    u32 packet;
    u8 pad84[0x8c];
} Channel;

extern Channel __CARDBlock[];
extern s32 DummyLen(void);
extern s32 ReadArrayUnlock(s32, u32, void *, s32, s32);
extern s32 __CARDReadStatus(s32, void *);
extern s32 EXIProbe(s32);
extern s32 EXIUnlock(s32);
extern void __CARDMountCallback(s32, s32);

#define LEFT_FEEDBACK(x) (~((x) ^ ((x) << 7) ^ ((x) << 15) ^ ((x) << 23)))
#define LEFT_STEP(x) ((x) = ((x) << 1) | ((LEFT_FEEDBACK(x) >> 30) & 2))

static inline u32 AdvanceState(u32 seed, u32 bit_count)
{
    u32 i;
    for (i = 0; i < bit_count; ++i)
        LEFT_STEP(seed);
    return seed | (LEFT_FEEDBACK(seed) >> 31);
}

void DoneCallback(DspTask *task)
{
    register s32 device;
    u32 key;
    u32 code;
    Channel *channel;
    u32 length;
    s32 result;
    u8 transfer[0x40];
    u8 response;
    /* Stack padding; the original purpose of these bytes is unknown. */
    u8 stack_padding[0x1c];

    for (device = 0; device < 2; ++device) {
        channel = &__CARDBlock[device];
        if (&channel->task == task)
            break;
    }

    key = *(u32 *)(((channel->packet + 0x2f) & 0xffffffe0) + 0x20);
    length = DummyLen();
    {
        /* The API takes a signed length. This scoped copy also preserves
         * MWCC's retail ordering of the argument register moves. */
        s32 read_length = length;
        code = (key ^ channel->state) & 0xffff0000;
        if (ReadArrayUnlock(device, code, transfer, read_length, 1) < 0) {
            EXIUnlock(device);
            __CARDMountCallback(device, -3);
            return;
        }
    }
    channel->state = AdvanceState(channel->state,
                                  (4 + length + channel->latency) * 8 + 1);

    length = DummyLen();
    code = ((key << 16) ^ channel->state) & 0xffff0000;
    if (ReadArrayUnlock(device, code,
                    transfer, length, 1) < 0) {
        EXIUnlock(device);
        __CARDMountCallback(device, -3);
        return;
    }

    result = __CARDReadStatus(device, &response);
    if (EXIProbe(device) == 0) {
        EXIUnlock(device);
        __CARDMountCallback(device, -3);
        return;
    }
    if (result == 0 && !(response & 0x40)) {
        EXIUnlock(device);
        result = -5;
    }
    __CARDMountCallback(device, result);
}
