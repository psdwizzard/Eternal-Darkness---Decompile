typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Command {
    u32 flags;
    u32 value;
} Command;

typedef struct Channel {
    u8 pad_000[8];
    u32 value_008;
} Channel;

typedef struct ChannelSlot {
    u8 pad_000[0xEC];
    int previous;
    int owner;
    u8 pad_0F4[4];
    Channel* channel;
    u8 pad_0FC[0x308];
} ChannelSlot;

typedef struct State {
    u8 pad_000[0xEC];
    u32 channel;
    u8 pad_0F0[4];
    u32 kind;
    u8 pad_0F8[8];
    u16 value_100;
    u8 pad_102[6];
    int channel_value;
    u8 pad_10C[0x10];
    u8 active;
    u8 special;
    u8 arg_11E;
    u8 arg_11F;
    u8 arg_120;
    u8 arg_121;
    u8 arg_122;
    u8 arg_123;
    u8 pad_124[0xB];
    u8 level;
    u8 pad_130[0x24];
    u32 arg_154;
    u8 pad_158[0x18];
    u32 arg_170;
    u8 pad_174[0x1F];
    u8 flag_193;
} State;

extern ChannelSlot* synthVoice;
extern u32 macStart(u16, u8, u8, u16, u8, u8, u8, u8,
                      u8, u8, u16, u8, int, u8, u8, int);
extern void synthFXCloneMidiSetup(ChannelSlot*, State*);

void mcmdPlayMacro(State* state, Command* command)
{
    int level;
    int adjusted;
    u32 channel;

    adjusted = state->level + (s8)((command->flags >> 8) & 0xFF);
    if (adjusted < 0) {
        level = 0;
    } else if (adjusted > 127) {
        level = 127;
    } else {
        level = adjusted;
    }
    if (state->special != 0) {
        level |= 0x80;
    }

    state->active = 1;
    channel = macStart(command->flags >> 16,
                          (command->value >> 16) & 0xFF,
                          command->value >> 24,
                          state->value_100,
                          level,
                          (state->arg_154 >> 16) & 0xFF,
                          (state->arg_170 >> 16) & 0xFF,
                          state->arg_121,
                          state->arg_122,
                          state->arg_123,
                          command->value & 0xFFFF,
                          state->arg_120,
                          0,
                          state->arg_11E,
                          state->arg_11F,
                          state->flag_193 == 0);
    state->active = 0;

    if (channel != -1) {
        state->channel_value = synthVoice[(u8)channel].channel->value_008;
        synthVoice[(u8)channel].owner = state->kind;

        if (state->channel != -1) {
            synthVoice[(u8)channel].previous = state->channel;
            synthVoice[(u8)state->channel].owner = channel;
        }
        state->channel = channel;

        if (state->special != 0) {
            synthFXCloneMidiSetup(&synthVoice[(u8)channel], state);
        }
    } else {
        state->channel_value = -1;
    }
}
