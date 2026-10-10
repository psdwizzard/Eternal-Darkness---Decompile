typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct State8006DFAC {
    u8 pad00[0x18];
    char text[0x50];
    u8 slot;
    u8 pad69;
    u8 flag6A;
    u8 flag6B;
} State8006DFAC;

typedef struct Context8006DFAC {
    u32 event;
    u8 pad04[4];
    s16 counter;
} Context8006DFAC;

extern Context8006DFAC *fn_8006ED98(State8006DFAC *);
extern void fn_8006BEE4(Context8006DFAC *, void (*)(void));
extern void fn_8006DEF8(State8006DFAC *, u32, void *, void *, int);
extern char *fn_800FD40C(char *, const char *);
extern void fn_801E7974(void *, u32);
extern void fn_8006EB60(void);
extern void fn_8006EA4C(void);
extern void fn_8006DE98(void);
extern void fn_800A1938(void);
extern void fn_800A0CC0(void);
extern char lbl_80243EE8[];
extern unsigned char lbl_80332140[];
extern void *lbl_8064C4E0;

void fn_8006DFAC(State8006DFAC *state)
{
    char *strings = lbl_80243EE8;
    Context8006DFAC *context;
    int i;

    context = fn_8006ED98(state);
    fn_8006BEE4(context, fn_8006EB60);
    state->flag6A = 0;
    state->flag6B = 0;
    state->slot = 4;
    fn_8006DEF8(state, context->event, 0, 0, 10);
    for (i = 0; i < 3; i++) {
        state->slot = i;
        fn_8006DEF8(state, context->event, 0, 0, 0);
    }
    state->slot = 0;

    switch (context->event) {
    case 0x22:
        fn_800FD40C(state->text, strings + 0x318);
        context->counter = 0;
        state->slot = 4;
        fn_8006DEF8(state, context->event, fn_800A1938, state, 1);
        state->slot = 0;
        break;
    case 0x24:
        fn_800FD40C(state->text, strings + 0x334);
        state->slot = 4;
        fn_8006DEF8(state, context->event, fn_800A0CC0, state, 0);
        fn_8006BEE4(context, fn_8006EB60);
        state->flag6A = 1;
        state->flag6B = 3;
        state->slot = 0;
        break;
    case 0x19:
        fn_800FD40C(state->text, strings + 0x350);
        break;
    case 0x1A:
        fn_800FD40C(state->text, strings + 0x364);
        break;
    case 0x1B:
        fn_8006BEE4(context, fn_8006EA4C);
        fn_801E7974(lbl_8064C4E0, 0x1DB);
        fn_800FD40C(state->text, strings + 0x37C);
        break;
    case 0x14:
        fn_8006BEE4(context, fn_8006DE98);
        *(u32 *)(lbl_80332140 + 0x10) |= 2;
        fn_800FD40C(state->text, strings + 0x398);
        break;
    case 0x1C:
        fn_800FD40C(state->text, strings + 0x3B4);
        break;
    case 0x26:
        fn_800FD40C(state->text, strings + 0x3D4);
        fn_8006BEE4(context, fn_8006EA4C);
        context->counter = 0;
        state->slot = 4;
        fn_8006DEF8(state, context->event, 0, 0, 0x708);
        state->slot = 0;
        break;
    }
}
