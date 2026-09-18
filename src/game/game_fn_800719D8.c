typedef short s16;

/*
 * NonMatching: the recovered state layout and call semantics are honest, but
 * The const-qualified inputs recover retail scheduling and all integer code.
 * MWCC still assigns the two float values to the opposite registers. Current
 * objdiff: 99.21875%, 128 bytes on both sides.
 */

typedef struct State {
    float x;
    float y;
    float z;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
} State;

typedef struct Owner {
    char pad_00[0xAC0];
    s16 value;
} Owner;

typedef struct Global {
    char pad_00[8];
    Owner *owner;
} Global;

extern const float lbl_8064E850;
extern const float lbl_8064E7E8;
extern State lbl_80312FD8;
extern Global lbl_80606328;
extern void fn_8015AA58(State *);

void fn_800719D8(void)
{
    State *state = &lbl_80312FD8;

    state->x = lbl_8064E850;
    state->y = lbl_8064E7E8;
    state->z = lbl_8064E7E8;
    state->a = 200;
    state->b = 250;
    state->c = 1;
    state->d = 2;
    state->e = 2;
    state->f = 0;
    state->g = lbl_80606328.owner->value;
    state->h = 2;
    state->i = 1;
    fn_8015AA58(state);
}
