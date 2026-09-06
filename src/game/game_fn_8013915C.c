typedef struct Slot {
    int resource_id;
    unsigned char pad04[0x4C];
} Slot;

typedef struct State {
    int id;
    int limit;
    int current;
    int pending;
    unsigned char pad10[0x2A8];
    Slot slots[2];
} State;

extern State lbl_805AE020;
extern void fn_80139464(int);

void fn_8013915C(void)
{
    State* state;

    state = &lbl_805AE020;
    if (state->pending != -1 &&
        state->pending != state->slots[state->id].resource_id) {
        fn_80139464(state->current);
    }
}
