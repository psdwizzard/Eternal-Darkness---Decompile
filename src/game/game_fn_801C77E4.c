typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Item {
    u8 type;
    u8 pad01;
    u16 value0;
    u16 value1;
    u16 value2;
    void* source;
} Item;

typedef struct State {
    u8 pad00[0x52];
    u8 count;
    u8 pad53[5];
    Item items[7];
} State;

int salRemoveStudioInput(State* state, void* source)
{
    int i;

    for (i = 0; i < state->count; i++) {
        if (state->items[i].source == source) {
            State* cursor = (State*)((u8*)state + i * sizeof(Item));
            for (; i <= state->count - 2; i++, cursor = (State*)((u8*)cursor + sizeof(Item))) {
                cursor->items[0] = cursor->items[1];
            }
            state->count--;
            return 1;
        }
    }
    return 0;
}
