typedef unsigned char u8;

typedef struct State800EB328 {
    u8 pad00[0x10];
    void* objects[3];
    void* resolved[3];
} State800EB328;

extern void* fn_801809A0(void*);

int fn_800EB328(State800EB328* state, int index)
{
    int valid = 0;

    if (state->objects[index] != 0) {
        valid = fn_801809A0(state->objects[index]) == state->resolved[index];
        if (valid == 0) {
            state->objects[index] = 0;
            state->resolved[index] = 0;
        }
    }
    return valid;
}
