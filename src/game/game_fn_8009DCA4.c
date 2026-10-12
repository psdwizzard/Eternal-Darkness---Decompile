typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry8009DCA4 {
    u8 index;
    u8 last_index;
    u8 reset_index;
    u8 limit;
    u8 pad04[0x28];
} Entry8009DCA4;

typedef struct State8009DCA4 {
    u8 pad00[0x18];
    char text[0x50];
    Entry8009DCA4 entries[3];
} State8009DCA4;

typedef struct Context8009DCA4 {
    u8 pad00[8];
    short counter;
    u8 pad0A[0xE];
    u32 flags;
} Context8009DCA4;

extern Context8009DCA4* fn_8006ED3C(State8009DCA4*, int, int*);
extern int fn_8006EB60(void*);
extern void fn_8006BEE4(int*, int);
extern void fn_8006DEF8(State8009DCA4*, u32, u32, u32, u16);
extern int fn_8009DDC8(State8009DCA4*);
extern int fn_800A0324(State8009DCA4*);
extern char* fn_800FD40C(char*, const char*);
extern char lbl_80245414[];

void fn_8009DCA4(register u32 state_address)
{
    State8009DCA4* state = (State8009DCA4*)state_address;
    int index;
    Context8009DCA4* context;
    int i;

    context = fn_8006ED3C(state, 0x13, &index);
    fn_8006BEE4((int*)context, (int)fn_8006EB60);
    state->entries[index].reset_index = 1;
    state->entries[index].limit = 4;
    state->entries[index].index = 4;
    fn_8006DEF8(state, 0x13, (u32)fn_8009DDC8, state_address, 0);
    for (i = 0; i < 3; i++) {
        state->entries[index].index = i;
        fn_8006DEF8(state, 0x13, (u32)fn_800A0324, state_address, 100);
    }
    state->entries[index].index = 0;
    context->flags |= 0x8014U;
    context->counter = 0;
    fn_800FD40C(state->text, lbl_80245414);
}
