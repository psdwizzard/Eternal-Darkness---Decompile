typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Owner Owner;
typedef struct Entry Entry;
typedef struct State8009EA3C State8009EA3C;
typedef struct State8009EAB0 State8009EAB0;

typedef struct Context8009E8E0 {
    s32 id;
    u8 pad04[4];
    s16 counter;
    u8 pad0A[0xE];
    u32 flags;
} Context8009E8E0;

typedef struct Slot8009E8E0 {
    u8 pad00[0x28];
    u8 index;
    u8 last_index;
    u8 reset_index;
    u8 limit;
} Slot8009E8E0;

typedef struct State8009E8E0 {
    u8 pad00[0x18];
    char text[0x28];
    Slot8009E8E0 slots[3];
} State8009E8E0;

extern Entry *fn_8006ED3C(Owner *owner, int id, int *index);
extern int fn_8006EB60(Owner *owner);
extern int fn_8009EA3C(State8009EA3C *state);
extern int fn_8009EAB0(State8009EAB0 *state);
extern void fn_8006BEE4(s32 *object, s32 value);
extern void fn_8006C9E4(s32 *object, s32 value);
extern void fn_8006DEF8(Owner *owner, u32 value, u32 first, u32 second, u16 third);
extern char *fn_800FD40C(char *destination, const char *source);
extern const char lbl_802454E8[];

void fn_8009E8E0(State8009E8E0 *state)
{
    int index;
    Context8009E8E0 *context;
    int i;
    u32 callback_argument;

    context = (Context8009E8E0 *)fn_8006ED3C((Owner *)state, 0x17, &index);
    fn_8006BEE4((s32 *)context, (s32)fn_8006EB60);
    fn_8006C9E4((s32 *)context, 0);
    /* Callback slots store argument addresses as 32-bit words. */
    callback_argument = (u32)state;
    state->slots[index].reset_index = 1;
    state->slots[index].limit = 1;
    state->slots[index].index = 4;
    fn_8006DEF8((Owner *)state, 0x17, (u32)fn_8009EA3C, callback_argument, 0);
    state->slots[index].index = 0;
    fn_8006DEF8((Owner *)state, 0x17, (u32)fn_8009EAB0, callback_argument, 2);
    i = 1;
    do {
        state->slots[index].index = i;
        fn_8006DEF8((Owner *)state, 0x17, 0, 0, 10);
        i++;
    } while (i < 3);
    state->slots[index].index = 0;
    fn_800FD40C(state->text, lbl_802454E8);
    context->counter = 0;
    context->flags &= ~0x40100U;
}
