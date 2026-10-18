typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct State {
    u8 active[16];
    u8 pending[16];
    u32 handles[16];
} State;

extern unsigned int rand(void);

void fn_8017F084(u8* object, u8* config)
{
    int count;
    State* state;
    int pair;
    u8 index;
    u32 zero;

    state = (State*)(object + 0x8C);
    index = 0;
    pair = 0;
    zero = 0;
    count = (config[0] & 0xFE) >> 1;
    *(u16*)(object + 0xEC) = *(u16*)(config + 0x18);

    while ((u8)pair < count) {
        rand();
        state->active[index] = zero;
        state->pending[index] = zero;
        state->handles[index] = zero;
        index++;
        state->active[index] = zero;
        state->pending[index] = zero;
        state->handles[index] = zero;
        index++;
        pair++;
    }
}
