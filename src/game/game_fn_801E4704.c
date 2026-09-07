typedef signed short s16;
typedef unsigned int u32;

typedef struct TextState {
    char pad0[8];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 flags;
} TextState;

extern u32 lbl_8064C2A8;
extern u32 lbl_8064D594;
extern float lbl_8064C314;
extern float lbl_8065127C;
extern char lbl_8064C32C;
extern char lbl_8064C330;

extern void fn_801ECD74(u32*);
extern void fn_801E5430(s16, s16);
extern void fn_801E3B08(char*);

void fn_801E4704(TextState* state)
{
    u32 color;

    if (state != 0) {
        state->flags |= 0x4000;
        if (!(state->flags & 8) && (state->flags & 1)) {
            lbl_8064D594 = lbl_8064C2A8;
            color = lbl_8064C2A8;
            fn_801ECD74(&color);
            fn_801E5430(state->x + state->width - 22,
                        state->y + state->height + 14);
            lbl_8064C314 = lbl_8065127C;
            if (state->flags & 0x40000) {
                fn_801E3B08(&lbl_8064C32C);
            } else {
                fn_801E3B08(&lbl_8064C330);
            }
        }
    }
}
