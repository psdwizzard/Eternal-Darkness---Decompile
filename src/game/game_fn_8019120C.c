typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad0[0xA];
    s16 position[3];
    s16 velocity[3];
    u8 pad16[0x15];
    u8 alpha;
    u8 pad2C[0xC];
} Entry;

typedef struct State {
    u8 pad0[0x2C];
    float position[3];
} State;

extern void fn_8018E230(void*, void*, int, u8, int, int);
extern unsigned int fn_800FBFB0(void);
extern void fn_80179904(s16*, s16);
extern void fn_8018F014(s16*, int);
extern void fn_80191F04(void*, u8, int);

void fn_8019120C(State* object, int index)
{
    State* state = object;
    Entry* entry = (Entry*)(*(u8**)((u8*)state + 0x4C) + index * 0x38);

    entry->alpha = (entry->alpha / -4) * -4;
    fn_8018E230(entry, &entry->alpha, 1, entry->alpha, -4, 0);

    state = (State*)((u8*)state + 0x8C);
    entry->velocity[0] = (s16)((float)entry->position[0] - state->position[0]);
    entry->velocity[1] = (s16)((float)entry->position[1] - state->position[1]);
    entry->velocity[2] = (int)((float)entry->position[2] - state->position[2]) >> 1;

    fn_80179904(entry->velocity, (s16)((fn_800FBFB0() & 7) + 16));
    fn_8018F014(entry->velocity, 2);
    fn_80191F04(state, (u8)index, 17);
}
