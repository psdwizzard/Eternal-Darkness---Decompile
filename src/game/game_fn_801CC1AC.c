typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct State {
    u8 pad[0x121];
    u8 channel;
    u8 layer;
    u8 pad2[0xA1];
    s16 value_a0;
    u8 pad3[0xA];
    s16 value_a1;
} State;

extern u32 inpTranslateExCtrl(u32);
extern u32 inpGetMidiCtrl(int, int, int);

u32 inpGetExCtrl(State* state, u32 control)
{
    u16 result;

    switch ((u8)inpTranslateExCtrl(control)) {
    case 0xA0:
        return state->value_a0 * 2 + 0x2000;
    case 0xA1:
        return state->value_a1 * 2 + 0x2000;
    default:
        if (state->channel != 0xFF) {
            result = inpGetMidiCtrl(control, state->channel, state->layer);
        } else {
            result = 0;
        }
        return result;
    }
}
