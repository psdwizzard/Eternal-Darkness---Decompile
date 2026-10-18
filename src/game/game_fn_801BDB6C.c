typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct StreamState {
    u8 pad_000[0x114];
    u64 flags;
    u8 pad_11C[0x24];
    u8 value_140;
    u8 value_141;
    u8 pad_142[2];
    u32 amount_144;
    u32 half_148;
} StreamState;
#pragma pack()

typedef struct StreamCommand {
    u32 flags;
    u32 value;
} StreamCommand;

extern void sndConvertMs(u32*);
extern void sndConvertTicks(u32*, StreamState*);

void mcmdVibrato(StreamState* state, StreamCommand* command)
{
    u32 amount;
    s8 first;
    s8 second;

    if ((command->flags >> 24) & 3) {
        state->flags |= 0x4000;
    } else {
        state->flags &= ~0x4000ULL;
    }

    amount = command->value >> 16;
    if ((command->value >> 8) & 1) {
        sndConvertMs(&amount);
    } else {
        sndConvertTicks(&amount, state);
    }

    if (amount != 0) {
        state->flags |= 0x2000;
        state->amount_144 = amount;
        first = command->flags >> 8;
        second = command->flags >> 16;
        if (first < 0) {
            if (second < 0) {
                state->value_141 = -second;
            } else {
                state->value_141 = second;
            }
            state->value_140 = -first;
            state->half_148 = state->amount_144 >> 1;
        } else {
            if (second < 0) {
                if (first == 0) {
                    state->value_141 = -second;
                    state->half_148 = state->amount_144 >> 1;
                } else {
                    state->value_141 = 100 - second;
                    state->half_148 = 0;
                    first--;
                }
            } else {
                state->value_141 = second;
                state->half_148 = 0;
            }
            state->value_140 = first;
        }
    } else {
        state->flags &= ~0x2000ULL;
    }
}
