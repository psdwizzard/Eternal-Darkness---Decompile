typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct McmdVoiceState {
    u8 pad000[0x121];
    u8 midi;
    u8 midiSet;
    u8 pad123[9];
    u16 curNote;
    s8 curDetune;
} McmdVoiceState;

typedef struct McmdCommandArgs {
    u32 flags;
    u32 value;
} McmdCommandArgs;

extern u16 fn_801CC2E4(void);
extern u32 fn_801C267C(McmdVoiceState*);
extern void fn_801CB470(u8, u8, u8);
extern void fn_801BD398(McmdVoiceState*, McmdCommandArgs*);

void fn_801BE5A0(McmdVoiceState* state, McmdCommandArgs* args)
{
    u8 tmp;
    s32 rangeHi;
    s32 rangeLo;
    u8 detune;
    u8 keyLo;
    u8 keyHi;

    if (((args->value >> 8) & 0xff) == 0) {
        keyHi = args->flags >> 0x18;
        keyLo = args->flags >> 8;
        detune = args->flags >> 0x18;
        if (((args->flags >> 8) & 0xff) > detune) {
            tmp = keyLo;
            keyLo = keyHi;
            keyHi = tmp;
        }
    } else {
        rangeLo = state->curNote;
        rangeLo -= (s32)((args->flags >> 8) & 0xff);
        rangeHi = state->curNote + (args->flags >> 0x18);
        keyLo = rangeLo < 0 ? 0 : rangeLo > 0x7f ? 0x7f : rangeLo;
        keyHi = rangeHi < 0 ? 0 : rangeHi > 0x7f ? 0x7f : rangeHi;
    }

    if ((u8)args->value != 0) {
        detune = (fn_801CC2E4() % 0xc9) - 100;
    } else {
        detune = (args->flags >> 0x10) & 0xff;
    }

    args->flags = (detune << 0x10) | 0x19 | ((keyLo + (fn_801CC2E4() % ((keyHi - keyLo) + 1))) << 8);
    args->value = 0;
    state->curNote = (args->flags >> 8) & 0x7f;
    state->curDetune = (s8)(args->flags >> 0x10);
    if (fn_801C267C(state) != 0) {
        fn_801CB470(state->midi, state->midiSet, state->curNote & 0xff);
    }
    args->flags = 4;
    fn_801BD398(state, args);
}
