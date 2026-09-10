typedef void (*Callback)(int);

typedef struct State {
    int duration;
    int delay;
    int value08;
    int value0C;
    int value10;
    int kind;
    int value18;
    int value1C;
    int value20;
    Callback callback;
    int callback_arg;
} State;

extern State lbl_805B701C;
extern int lbl_8064C4F4;
extern int lbl_8064C5C0;
extern int lbl_8064D18C;
extern float lbl_80650630;
extern int lbl_8065063C;

extern void fn_801F348C(int*, int);
extern void fn_80159440(int, int);
extern void fn_80180C94(void);
extern void fn_80200EAC(int, int, int, float, int);
extern void fn_801597BC(int, int, int, int, int);

void fn_8015CA08(void)
{
    State* state = &lbl_805B701C;

    if (state->duration != 0) {
        state->duration--;
        if (state->delay != 0 && --state->delay == 0) {
            int value = lbl_8065063C;
            fn_801F348C(&value, state->duration);
        }

        state = &lbl_805B701C;
        if (state->duration == 0) {
            if (state->kind == 0x11) {
                fn_80159440(state->value08, state->value10);
                if (lbl_8064C4F4 == 0) {
                    fn_80180C94();
                    fn_80200EAC(0x3e, 0, 0, lbl_80650630, lbl_8064D18C);
                }
                lbl_8064C5C0 = 0;
            } else {
                fn_801597BC(state->value08, state->value1C, state->value20,
                            state->value0C, state->value10);
            }

            state = &lbl_805B701C;
            if (state->callback != 0)
                state->callback(state->callback_arg);
        }
    }
}
