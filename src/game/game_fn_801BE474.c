typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct StreamState {
    u8 pad_000[0x114];
    u64 flags_114;
    u8 pad_11C[0x38];
    u32 scale_154;
    u8 pad_158[0x3C];
    s32 delta_194;
    u32 value_198;
    u32 target_19C;
} StreamState;
#pragma pack()

typedef union CommandWord {
    u32 raw;
    struct {
        unsigned high : 8;
        unsigned byte_1 : 8;
        unsigned byte_2 : 8;
        unsigned low : 8;
    } bytes;
} CommandWord;

typedef struct StreamCommand {
    CommandWord value;
    CommandWord flags;
} StreamCommand;

extern void sndConvertMs(u32*);
extern void sndConvertTicks(u32*, StreamState*);
extern u32 sndConvert2Ms(u32);
extern u8* dataGetCurve(u32);

void DoEnvelopeCalculation(StreamState* state, StreamCommand* command, u32 target)
{
    u32 duration;
    u32 divisor;
    u32 value;
    u32 resource;
    u8* table;
    u32 index;
    u32 result;
    u16 fraction;
    u32 current;
    /*
     * These otherwise-unused volatile slots are load-bearing MWCC frame evidence:
     * removing them shrinks the frame from 0x38 to 0x30 and moves duration from
     * 0x1c(r1) to 0x14(r1). Retail uses the larger frame and 0x1c slot.
     */
    volatile u32 stack_align;
    volatile u32 stack_align_2;

    duration = command->flags.raw >> 16;
    if ((command->flags.raw >> 8) & 1) {
        sndConvertMs(&duration);
    } else {
        sndConvertTicks(&duration, state);
    }
    divisor = sndConvert2Ms(duration);
    if (divisor == 0) {
        divisor = 1;
    }

    value = (state->scale_154 * ((command->value.raw >> 8) & 0xFF)) >> 7;
    value += command->value.raw & 0xFF0000;
    if (value > 0x7F0000) {
        value = 0x7F0000;
    }

    resource = (u8)(command->value.raw >> 24);
    resource |= ((u8)command->flags.raw << 8);
    if ((u16)resource != 0xFFFF) {
        table = dataGetCurve(resource);
        if (table != 0) {
            index = value >> 16;
            fraction = (u16)value;
            if (index < 0x7F) {
                current = table[index];
                result = table[index + 1];
                result = (result - current) * fraction;
                value = result + (current << 16);
            } else {
                value = table[index] << 16;
            }
        }
    }

    state->value_198 = value;
    state->target_19C = target;
    state->delta_194 = ((s32)value - (s32)target) / (s32)divisor;
    state->scale_154 = target;
    state->flags_114 |= 0x8000ULL;
}
