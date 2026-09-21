typedef signed char s8;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamCommand {
    u32 value;
    u32 adjustment;
} StreamCommand;

/* Flags occupy a packed 64-bit word; this command sets bit 45. */
#pragma pack(4)
typedef struct StreamState {
    u8 pad_000[0x114];
    unsigned long long flags_114;
    u8 pad_11C[0x54];
    u32 base_170[2];
    u32 delta_178[2];
    u32 target_180[2];
    u32 step_188[2];
} StreamState;
#pragma pack()

extern void fn_801CC408(u32*);

void fn_801BE354(StreamState* state, StreamCommand* command, u8 index)
{
    s32 value;
    s32 adjustment;

    value = command->value >> 16;
    state->step_188[index] = value;
    fn_801CC408(&state->step_188[index]);
    adjustment = (s8)command->adjustment << 16;
    state->base_170[index] = (command->value << 8) & 0x00FF0000;
    state->target_180[index] = state->base_170[index] + adjustment;
    if (state->step_188[index] != 0) {
        state->delta_178[index] = adjustment / value;
    } else {
        state->delta_178[index] = adjustment;
    }
    state->flags_114 |= 0x200000000000ULL;
}
