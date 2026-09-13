typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RangeState {
    int distance;
    int span;
    void* previous;
    void* current;
} RangeState;

typedef struct Runtime {
    u8 pad0[0x101];
    u8 scale;
} Runtime;

extern int fn_801285C0(void*);

void fn_801274F4(void* entries, u16 count, Runtime* runtime,
                 RangeState* state, int value, int update,
                 int* output, int* wrapped_output)
{
    int index;
    int wrapped;

    wrapped = 0;
    state->distance = 0;
    state->span = 0;
    if (state->previous == 0 || update == 0) {
        if (value >= 0) {
            state->previous = entries;
            index = 1;
        } else {
            state->previous = (u8*)entries + (count - 1) * 0xC;
            index = count - 2;
        }
    } else {
        state->previous = state->current;
        wrapped = 1;
        value = ((unsigned int)value >> 31) - 1;
        index = (count - 1) & ~value;
    }
    if (count > index) {
        state->current = (u8*)entries + index * 0xC;
    } else {
        state->current = state->previous;
    }
    if (wrapped != 0) {
        state->span = runtime->scale << 16;
    } else {
        state->span = fn_801285C0(state->current) - fn_801285C0(state->previous) < 0
                          ? -(fn_801285C0(state->current) - fn_801285C0(state->previous))
                          : fn_801285C0(state->current) - fn_801285C0(state->previous);
    }
    if (wrapped != 0) {
        *output = fn_801285C0(state->current);
        *wrapped_output = 1;
    } else {
        *output = fn_801285C0(state->previous);
    }
}
