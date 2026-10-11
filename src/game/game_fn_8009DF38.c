typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Context {
    u8 pad00[0x18];
    u32 flags;
} Context;

typedef struct Work {
    u8 pad00[0x20];
    u32 flags;
} Work;

typedef struct Slot {
    u8 pad00[0x28];
    u8 count;
    u8 pad29;
    u8 field2A;
    u8 field2B;
} Slot;

typedef struct State {
    u8 pad00[0x18];
    char name[0x28];
    Slot slots[3];
    Work *work;
} State;

typedef struct ModeState {
    u8 pad00[8];
    int mode;
} ModeState;

extern Context *fn_8006ED3C(State *, int, int *);
extern void fn_8006BEE4(int *, int);
extern void fn_8006C9E4(int *, int);
struct Owner;
extern int fn_8006EB60(struct Owner *);
extern int fn_8009E0D4(State *);
extern int fn_8009E130(State *);
extern void fn_8006DEF8();
extern char *fn_800FD40C(char *, const char *);
extern ModeState lbl_803003C8;
extern const char lbl_80245448[];

void fn_8009DF38(register State *state)
{
    int index;
    Context *context;
    Work *work;
    int i;

    context = fn_8006ED3C(state, 13, &index);
    fn_8006BEE4((int *)context, (int)fn_8006EB60);
    fn_8006C9E4((int *)context, 0);
    work = state->work;
    context->flags &= ~0x100U;
    state->slots[index].field2A = 3;
    state->slots[index].field2B = 4;
    state->slots[index].count = 4;
    fn_8006DEF8(state, 13, fn_8009E0D4, state, 0);
    if (lbl_803003C8.mode == 7 || lbl_803003C8.mode == 10) {
        for (i = 0; i < 3; i++) {
            state->slots[index].count = i;
            fn_8006DEF8(state, 13, fn_8009E130, state, 700);
        }
    } else {
        for (i = 0; i < 3; i++) {
            state->slots[index].count = i;
            fn_8006DEF8(state, 13, fn_8009E130, state, 300);
        }
    }
    state->slots[index].count = 0;
    work->flags |= 4;
    fn_800FD40C(state->name, lbl_80245448);
}
