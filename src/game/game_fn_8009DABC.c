typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry8009DABC {
    u8 index;
    u8 last_index;
    u8 reset_index;
    u8 limit;
    u8 pad04[0x28];
} Entry8009DABC;

typedef struct State8009DABC {
    u8 pad00[0x18];
    char text[0x50];
    Entry8009DABC entries[3];
} State8009DABC;

typedef struct Context8009DABC {
    u8 pad00[8];
    short counter;
    u8 pad0A[0xE];
    u32 flags;
} Context8009DABC;

extern Context8009DABC* fn_8006ED3C(State8009DABC*, int, int*);
extern int fn_8006EB60(void*);
extern void fn_8006BEE4(int*, int);
extern void fn_8006DEF8(State8009DABC*, u32, u32, u32, u16);
extern int fn_8009DBE4(State8009DABC*);
extern int fn_8009EF8C(State8009DABC*);
extern char* fn_800FD40C(char*, const char*);
extern char lbl_802453F8[];

void fn_8009DABC(register u32 state_address)
{
    State8009DABC* state = (State8009DABC*)state_address;
    int index;
    Context8009DABC* context;
    int i;

    context = fn_8006ED3C(state, 0x12, &index);
    fn_8006BEE4((int*)context, (int)fn_8006EB60);
    state->entries[index].reset_index = 1;
    state->entries[index].limit = 4;
    state->entries[index].index = 4;
    fn_8006DEF8(state, 0x12, (u32)fn_8009DBE4, state_address, 0);
    context->counter = 0;
    for (i = 0; i < 3; i++) {
        state->entries[index].index = i;
        fn_8006DEF8(state, 0x12, (u32)fn_8009EF8C, state_address, 100);
    }
    state->entries[index].index = 0;
    context->flags |= 0x4014;
    fn_800FD40C(state->text, lbl_802453F8);
}
