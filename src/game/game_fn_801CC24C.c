typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct State {
    u8 pad[0x121];
    u8 channel;
    u8 layer;
} State;

extern u8 inpTranslateExCtrl(u8);
extern void inpSetMidiCtrl14(u8, u8, u8, u16);

void inpSetExCtrl(State* state, u8 control, s16 value)
{
    value = value < 0 ? 0 : value > 0x3FFF ? 0x3FFF : value;

    switch (inpTranslateExCtrl(control)) {
    default:
        if (state->channel != 0xFF) {
            inpSetMidiCtrl14(control, state->channel, state->layer, value);
        }
        break;
    case 0xA0:
    case 0xA1:
        break;
    }
}
