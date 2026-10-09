typedef unsigned char u8;

typedef struct State800EB3A4 {
    u8 pad00[0x10];
    void* objects[3];
    void* resolved[3];
    u8 pad28[0xE4 - 0x28];
    void* pending;
    u8 padE8[0x178 - 0xE8];
    int index;
} State800EB3A4;

extern int lbl_8064CB18;
extern void* fn_801809A0(void*);

void fn_800EB3A4(State800EB3A4* state)
{
    lbl_8064CB18++;
    if (state->index != -1 && state->pending != 0) {
        state->objects[state->index] = state->pending;
        state->resolved[state->index] =
            fn_801809A0(state->objects[state->index]);
        state->pending = 0;
        state->index = -1;
        lbl_8064CB18 = 0;
    }
}
