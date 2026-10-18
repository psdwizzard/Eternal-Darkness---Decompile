typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct StreamState {
    u8 pad_00[0x34];
    u8* table_base;
    u8* current_entry;
    u8 pad_3C[0x54];
    u64 base_time;
    u64 current_time;
    u64 previous_time;
    u8 pad_A8[2];
    u16 countdown;
    u8 pad_AC[0x48];
    u32 kind;
    u8 pad_F8[0x1C];
    u64 flags;
} StreamState;
#pragma pack()

typedef struct StreamCommand {
    u32 flags;
    u32 value;
} StreamCommand;

extern unsigned int sndRand(void);
extern unsigned int hwIsActive(unsigned int);

void mcmdLoop(StreamState* state, StreamCommand* command)
{
    u16 countdown;

    if (state->countdown == 0) {
        if ((command->flags >> 16) & 1) {
            state->countdown = (u16)sndRand() % (u16)(command->value >> 16);
        } else {
            state->countdown = command->value >> 16;
        }

        if (state->countdown != 0xFFFF) {
            state->countdown++;
        } else {
            goto update;
        }
    } else if (state->countdown == 0xFFFF) {
        goto update;
    }

    countdown = state->countdown - 1;
    state->countdown = countdown;
    if (countdown == 0) {
        return;
    }

update:
    if ((command->flags >> 8) & 1) {
        if ((state->flags & 0x10000000008ULL) == 8) {
            state->countdown = 0;
            return;
        }
    }

    if ((command->flags >> 24) & 1) {
        if (!(state->flags & 0x20) && !hwIsActive(state->kind & 0xFF)) {
            state->countdown = 0;
            return;
        }
    }

    state->current_entry = state->table_base + ((command->value & 0xFFFF) << 3);
}
