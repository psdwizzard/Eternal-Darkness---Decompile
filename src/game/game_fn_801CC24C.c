typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct State {
    u8 pad[0x121];
    u8 channel;
    u8 layer;
} State;

extern u8 fn_801CC13C(u8);
extern void fn_801CAD90(u8, u8, u8, u16);

void fn_801CC24C(State* state, u8 control, s16 value)
{
    value = value < 0 ? 0 : value > 0x3FFF ? 0x3FFF : value;

    switch (fn_801CC13C(control)) {
    default:
        if (state->channel != 0xFF) {
            fn_801CAD90(control, state->channel, state->layer, value);
        }
        break;
    case 0xA0:
    case 0xA1:
        break;
    }
}
