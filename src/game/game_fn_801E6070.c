typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct TextState {
    float scale;
    u8 color[4];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 flags;
    s16 phase;
    u8 font;
    s8 align;
    s8 text[1];
} TextState;

extern u32 lbl_8064D5A8;
extern char lbl_802649C8[];
extern char lbl_802649EC[];
extern float lbl_80651284;

extern void fn_801E7FDC(char*, ...);
extern void fn_801E5FB0(TextState*);
extern void fn_801E3AA4(int);
extern void fn_801E5430(s16, s16);
extern void fn_801E47B8(TextState*);
extern void fn_801E5AD0(u8);
extern void fn_801E56AC(char*, ...);

void fn_801E6070(TextState* state)
{
    s16 y;

    if (state == 0)
        return;
    if (state->text[2] == 0 && state->text[3] == 0)
        return;

    y = state->y;
    if ((state->flags & 0x100) && (lbl_8064D5A8 & 1)) {
        state->phase++;
        state->phase = 0 < state->phase ? 0 : state->phase;
    }
    if (state->flags & 0x10)
        y -= state->phase;

    if (state->flags & 0x40) {
        if (state->color[3] < 230) {
            state->color[3] += 25;
        } else {
            state->color[3] = 0xFF;
            state->flags = __rlwinm(state->flags, 0, 26, 24);
            if (state->flags & 0x20)
                state->flags |= 0x80;
        }
    } else if (state->flags & 0x80) {
        if (state->color[3] > 25) {
            state->color[3] -= 25;
        } else {
            state->color[3] = 0;
            state->flags = __rlwinm(state->flags, 0, 25, 23);
            if (state->flags & 0x20) {
                state->flags |= 0x40;
            } else {
                fn_801E7FDC(lbl_802649C8, state);
                fn_801E5FB0(state);
                return;
            }
        }
    }

    fn_801E3AA4(state->text[1]);
    fn_801E5430(state->x, y);
    fn_801E47B8(state);
    if (state->flags & 0x8000) {
        fn_801E5430(320, 240);
        fn_801E5AD0(99);
        fn_801E56AC(lbl_802649EC, lbl_80651284);
    }
}
