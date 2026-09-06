typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Runtime {
    u8 pad0[0xB8];
    void* table;
} Runtime;

typedef struct Owner {
    u8 pad0[0x15C];
    void* volatile states;
} Owner;

typedef struct State {
    u8 pad0[4];
    int direction;
} State;

typedef struct Pair {
    u32 count;
    void* entries;
} Pair;

#define FN_80128E30_RETURN Runtime*
#define FN_80128E30_PARAMETERS Owner*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern void fn_80127128(void*, u32, State*, int, int*);

void fn_80127178(Owner* owner, int index, int direction)
{
    u32 count;
    State* state;
    Pair* pair;
    Runtime* runtime;

    runtime = fn_80128E30(owner);
    pair = (Pair*)((u8*)*(void**)((u8*)runtime->table + 4) + index * 8 + 0x10);
    count = pair->count;
    if (count != 0) {
        state = (State*)((u8*)owner->states + index * 0x18);
        fn_80127128(pair->entries, count, state, direction, (int*)state);
    }
    state = (State*)((u8*)owner->states + index * 0x18);
    state->direction = direction;
}
