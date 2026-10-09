typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Pair {
    u32 first;
    u32 second;
} Pair;

typedef struct RotationState {
    u8 pad_00[0x24];
    u16 flags;
    u8 pad_26[0x46];
    Pair previous;
    Pair current;
    Pair target;
    float amount;
    float step;
} RotationState;

extern const float lbl_806501D8;
extern const float lbl_806501E0;

void fn_8012D964(RotationState* state)
{
    Pair saved = state->current;

    state->current = state->target;
    state->previous = state->target;
    state->target = saved;
    state->amount = lbl_806501D8;
    state->step = state->step;
    if (state->flags & 0x80) {
        state->step *= lbl_806501E0;
    }
}
