typedef struct ObjectState {
    unsigned char pad00[0x8C];
    struct SelectionState *selection;
} ObjectState;

typedef struct SelectionState {
    unsigned char pad00[0x167];
    unsigned char counter;
} SelectionState;

extern int fn_800BCDF0(void *object);
extern ObjectState *fn_80201B8C();

int fn_800BCE94(void *object, int limit)
{
    SelectionState *state;
    int result = 0;

    state = fn_80201B8C(object)->selection;

    if (state->counter >= limit) {
        fn_800BCDF0(object);
        result = 1;
        state->counter = 0;
    }

    return result;
}
