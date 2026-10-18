typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Result { u32 first, second, third; } Result;

/* The EXI receive area follows reserved transfer workspace on the stack. */
typedef struct TransferScratch {
    u8 reserved_before[0x64];
    u32 response[5];
    u8 reserved_after[0x40];
} TransferScratch;

typedef struct DspTask {
    u32 state;
    volatile u32 command;
    u32 flags;
    u16 *data_address;
    u32 data_size;
    u32 zero14;
    u16 *dram;
    u32 dram_size;
    u32 dram_address;
    u16 kind;
    u16 resume_vector;
    void (*callback)(struct DspTask *);
    void (*resume_callback)(struct DspTask *);
    void (*done_callback)(struct DspTask *);
    void (*request_callback)(struct DspTask *);
    struct DspTask *next;
    struct DspTask *prev;
} DspTask;

typedef struct TransferPacket {
    void *source;
    u32 length;
    u32 zero;
    void *destination;
} TransferPacket;

typedef struct Channel {
    u8 pad00[0x2c];
    u32 state;
    DspTask task;
    u8 pad70[0x10];
    TransferPacket *packet;
    u8 pad84[0x8c];
} Channel;

extern Channel __CARDBlock[];
extern u32 lbl_8064C448;
extern u8 CardData[];
extern u32 OSGetTick(void);
extern s32 DummyLen(void);
extern s32 ReadArrayUnlock(s32, u32, void *, s32, s32);
extern u32 bitrev(u32);
extern void DCFlushRange(void *, u32);
extern void DCInvalidateRange(void *, u32);
extern DspTask *DSPAddTask(DspTask *);
extern void InitCallback(DspTask *);
extern void DoneCallback(DspTask *);

/* Complemented feedback bits for the two transfer directions. */
#define RIGHT_BIT(x) (~((x) ^ ((x) >> 7) ^ ((x) >> 15) ^ ((x) >> 23)))
#define LEFT_BIT(x) (~((x) ^ ((x) << 7) ^ ((x) << 15) ^ ((x) << 23)))
#define RIGHT_STEP(x) ((x) = ((x) >> 1) | ((RIGHT_BIT(x) << 30) & 0x40000000))
#define LEFT_STEP(x) ((x) = ((x) << 1) | ((LEFT_BIT(x) >> 30) & 2))

static inline void AdvanceLeft(Channel *ch, u32 count)
{
    u32 i;
    u32 state = ch->state;
    for (i = 0; i < count; ++i) {
        LEFT_STEP(state);
    }
    ch->state = state | (LEFT_BIT(state) >> 31);
}

s32 __CARDUnlock(s32 channel, Result *result)
{
    Channel *ch;
    DspTask *task;
    TransferPacket *packet;
    u32 *message;
    u32 *reply;
    TransferScratch scratch;
    u32 state;
    u32 second, third, fourth, fifth;
    s32 first;
    u32 address;
    u32 tick;
    u32 length, read_length;
    u32 count, i;

    ch = &__CARDBlock[channel];
    task = &ch->task;
    packet = ch->packet;
    message = (u32 *)((u8 *)packet + 0x10);
    message = (u32 *)(((u32)message + 31) & ~31);
    reply = (u32 *)((u8 *)message + 0x20);

    lbl_8064C448 = OSGetTick();
    address = 0x7fec8000;
    tick = lbl_8064C448;
    lbl_8064C448 = tick * 0x41c64e6d + 0x3039;
    address |= (lbl_8064C448 >> 16) & 0x7fff;
    address &= ~0xfff;
    length = DummyLen();
    {
        /* EXI takes a signed byte count; keep the bit counts unsigned. */
        s32 transfer_length = length;
        if (ReadArrayUnlock(channel, address,
                       (u32 *)((u8 *)&scratch + sizeof(scratch.reserved_before)),
                       transfer_length, 0) < 0)
            return -3;
    }

    /* Fold the transmitted address bits into the channel state. */
    count = (i = length * 8) + 1;
    for (i = 0; i < count; ++i) {
        RIGHT_STEP(address);
    }
    ch->state = address | (RIGHT_BIT(address) << 31);
    ch->state = bitrev(ch->state);

    read_length = DummyLen();
    {
        s32 transfer_length = read_length + 0x14;
        if (ReadArrayUnlock(channel, 0, (u32 *)&scratch.response[0],
                       transfer_length, 1) < 0)
            return -3;
    }

    /* Read the five response words before advancing the receive state. */
    first = scratch.response[0];
    fifth = scratch.response[4];
    third = scratch.response[2];
    fourth = scratch.response[3];
    second = scratch.response[1];
    state = ch->state;
    first ^= state;
    AdvanceLeft(ch, 32);

    state = ch->state;
    second ^= state;
    AdvanceLeft(ch, 32);

    state = ch->state;
    third ^= state;
    AdvanceLeft(ch, 32);

    state = ch->state;
    fourth ^= state;
    AdvanceLeft(ch, 32);

    state = ch->state;
    fifth ^= state;
    count = (i = read_length * 8);
    for (i = 0; i < count; ++i) {
        LEFT_STEP(state);
    }
    ch->state = state | (LEFT_BIT(state) >> 31);

    state = ch->state;
    for (i = 0; i < 0x21; ++i) {
        LEFT_STEP(state);
    }
    ch->state = state | (LEFT_BIT(state) >> 31);

    message[0] = fourth;
    message[1] = fifth;
    packet->source = message;
    packet->length = 8;
    packet->destination = reply;
    packet->zero = 0;
    DCFlushRange(message, 8);
    DCInvalidateRange(reply, 4);
    DCFlushRange(packet, 0x10);

    task->command = 0xff;
    task->data_address = (u16 *)((u32)CardData + 0x80000000);
    task->data_size = 0x160;
    task->zero14 = 0;
    task->kind = 0x10;
    task->callback = InitCallback;
    task->resume_callback = 0;
    task->done_callback = DoneCallback;
    task->request_callback = 0;
    DSPAddTask(task);
    result->first = first;
    result->second = second;
    result->third = third;
    return 0;
}
