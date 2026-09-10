typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SYNTH_VOICE SYNTH_VOICE;

typedef struct MSTEP {
    u32 para1;
    u32 para2;
} MSTEP;

extern u32 fn_801BE9D8(SYNTH_VOICE*, u32, u8);
extern void fn_801BEAA4(SYNTH_VOICE*, u32, u8, s32);

#define varGet32 fn_801BE9D8
#define varSet32 fn_801BEAA4

static inline s16 varGetSigned(SYNTH_VOICE* state, u32 useExCtrl, u8 index)
{
    return (s16)varGet32(state, useExCtrl, index);
}

static inline void varSet(SYNTH_VOICE* state, u8 useExCtrl, u8 index, s16 value)
{
    varSet32(state, useExCtrl, index, value);
}

void fn_801BEB08(SYNTH_VOICE* state, MSTEP* operation, u8 opcode)
{
    s16 s1;
    s16 s2;
    s32 result;

    s1 = varGetSigned(state, (u8)(operation->para1 >> 24), operation->para2);
    if (opcode == 4) {
        s2 = operation->para2 >> 8;
    } else {
        s2 = varGetSigned(state, (u8)(operation->para2 >> 8),
                          operation->para2 >> 16);
    }

    switch (opcode) {
    case 4:
    case 0:
        result = s1 + s2;
        break;
    case 1:
        result = s1 - s2;
        break;
    case 2:
        result = s1 * s2;
        break;
    case 3:
        result = s2 != 0 ? s1 / s2 : 0;
        break;
    }

    {
        u8 control = operation->para1 >> 8;
        u8 index = operation->para1 >> 16;
        s16 clamped = result < -32768 ? -32768
                                     : result > 32767 ? 32767 : result;

        varSet(state, control, index, clamped);
    }
}
