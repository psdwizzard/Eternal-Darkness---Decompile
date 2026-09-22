/* NonMatching: independent honest-C reconstruction of the volume-ramp
 * dispatcher. The three retail paths deliberately contain separate ramp
 * loops; preserving that source-level shape is important to its codegen. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ramp {
    float current;
    float target;
    float previous;
    float step;
    float reciprocal;
    u8 pad14[0x14];
    u32 voice;
    u8 value;
    u8 type;
    u8 pad2E[2];
} Ramp;

typedef struct RampState {
    u8 pad[0x5D4];
    Ramp ramps[32];
} RampState;

extern u8 lbl_80619860[];
extern u32 lbl_8064D3C8;
extern const float lbl_80650EC8;
extern void fn_801CC408(u32*);
extern void fn_801B7A10(Ramp*);

#define SET_RAMP(ramp_, voice_)                                               \
    do {                                                                      \
        u32 ramp_duration = duration;                                         \
        (ramp_)->value = value;                                               \
        (ramp_)->voice = (voice_);                                            \
        if (ramp_duration != 0) {                                             \
            (ramp_)->previous = (ramp_)->current;                             \
            (ramp_)->target = target;                                         \
            (ramp_)->step = 0.0f;                                             \
            (ramp_)->reciprocal = 1.0f / (float)ramp_duration;                \
        } else {                                                              \
            (ramp_)->target = target;                                         \
            (ramp_)->current = target;                                        \
            if ((ramp_)->voice != 0xFFFFFFFFU) {                              \
                fn_801B7A10(ramp_);                                           \
            }                                                                 \
        }                                                                     \
    } while (0)

void fn_801B8164(u8 amount, u16 duration_arg, u8 selector, u8 value,
                 u32 voice)
{
    u32 duration = duration_arg;
    u8* base = lbl_80619860;
    u32 i;
    Ramp* ramp;
    u8 type;
    float target;

    if (duration_arg != 0) {
        fn_801CC408(&duration);
    }

    switch (selector) {
    case 0xFF:
        target = lbl_80650EC8 * (float)amount;
        for (ramp = (Ramp*)(base + 0x5D4), i = 0; i < 32;
             ++i, ++ramp) {
            if (ramp->type == 0 || ramp->type == 1) {
                SET_RAMP(ramp, 0xFFFFFFFFU);
                lbl_8064D3C8 |= 1U << i;
            }
        }
        break;

    case 0xFC:
        target = lbl_80650EC8 * (float)amount;
        for (ramp = (Ramp*)(base + 0x5D4), i = 0; i < 32;
             ++i, ++ramp) {
            if (ramp->type == 2 || ramp->type == 3) {
                SET_RAMP(ramp, 0xFFFFFFFFU);
                lbl_8064D3C8 |= 1U << i;
            }
        }
        break;

    case 0xFA:
        type = 2;
        goto update_type;
    case 0xFB:
        type = 3;
        goto update_type;
    case 0xFD:
        type = 0;
        goto update_type;
    case 0xFE:
        type = 1;
update_type:
        target = lbl_80650EC8 * (float)amount;
        for (ramp = (Ramp*)(base + 0x5D4), i = 0; i < 32;
             ++i, ++ramp) {
            if (ramp->type == type) {
                SET_RAMP(ramp, 0xFFFFFFFFU);
                lbl_8064D3C8 |= 1U << i;
            }
        }
        break;

    default: {
        u32 ramp_duration = duration;
        RampState* state = (RampState*)((Ramp*)base + selector);
        u32* voice_field;
        state->ramps[0].value = value;
        *(voice_field = &state->ramps[0].voice) = voice;
        if (ramp_duration != 0) {
            state->ramps[0].previous = state->ramps[0].current;
            state->ramps[0].target = lbl_80650EC8 * (float)amount;
            state->ramps[0].step = 0.0f;
            state->ramps[0].reciprocal = 1.0f / (float)ramp_duration;
        } else {
            ramp = &state->ramps[0];
            target = lbl_80650EC8 * (float)amount;
            state->ramps[0].target = target;
            state->ramps[0].current = target;
            if (*voice_field != 0xFFFFFFFFU) {
                fn_801B7A10(ramp);
            }
        }
        lbl_8064D3C8 |= 1U << selector;
        break;
    }
    }
}

#undef SET_RAMP
