typedef unsigned int u32;
typedef signed short s16;

typedef struct State {
    char pad00[0x0c];
    float point[3];
    float threshold_a;
    float threshold_b;
    u32 flags;
    u32 value_a0;
    u32 value_a1;
    u32 value_b0;
    u32 value_b1;
    s16 event_a0;
    s16 event_b0;
    s16 event_a1;
    s16 event_b1;
} State;

extern int fn_8013D618(void*, void*, void*, float, float);
extern void fn_8016B400(s16, State*, int);
extern float PSVECDotProduct(void*, void*);

void fn_80155814(State* state, void* context, void* object, int alternate)
{
    u32 mask_a;
    u32 bit_a;
    u32 mask_b;
    u32 bit_b;

    if (state == 0)
        return;

    if (alternate == 0) {
        mask_a = 2;
        bit_a = 1;
        mask_b = 8;
        bit_b = 4;
    } else {
        mask_a = 0x20;
        bit_a = 0x10;
        mask_b = 0x80;
        bit_b = 0x40;
    }

    if (fn_8013D618(object, context, state, (float)state->value_a0,
                    state->threshold_a)) {
        if (!(state->flags & mask_a) && (state->flags & bit_a) &&
            state->event_a0 != -1)
            fn_8016B400(state->event_a0, state, 0);
        state->flags |= mask_a;
    } else {
        state->flags &= ~mask_a;
    }

    if (fn_8013D618(object, context, state, (float)state->value_a1,
                    state->threshold_a)) {
        state->flags |= bit_a;
    } else if ((state->flags & bit_a) || (state->flags & mask_a)) {
        state->flags &= ~mask_a;
        state->flags &= ~bit_a;
        if (PSVECDotProduct(object, state) > state->threshold_a &&
            state->event_a1 != -1)
            fn_8016B400(state->event_a1, state, 0);
    }

    if (fn_8013D618(object, context, state->point, (float)state->value_b0,
                    state->threshold_b)) {
        if (!(state->flags & mask_b) && (state->flags & bit_b) &&
            state->event_b0 != -1)
            fn_8016B400(state->event_b0, state, 0);
        state->flags |= mask_b;
    } else {
        state->flags &= ~mask_b;
    }

    if (fn_8013D618(object, context, state->point, (float)state->value_b1,
                    state->threshold_b)) {
        state->flags |= bit_b;
    } else if ((state->flags & bit_b) || (state->flags & mask_b)) {
        state->flags &= ~mask_b;
        state->flags &= ~bit_b;
        if (PSVECDotProduct(object, state->point) > state->threshold_b &&
            state->event_b1 != -1)
            fn_8016B400(state->event_b1, state, 0);
    }
}
