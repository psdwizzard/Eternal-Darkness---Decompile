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

int salAddStudioInput(State* state, u8* source)
{
    u8 value;

    if (state->count < 7) {
        state->items[state->count].type = source[3];
        value = source[0];
        state->items[state->count].value0 = (value << 8) | (value << 1);
        value = source[1];
        state->items[state->count].value1 = (value << 8) | (value << 1);
        value = source[2];
        state->items[state->count].value2 = (value << 8) | (value << 1);
        state->items[state->count].source = source;
        state->count++;
        return 1;
    }
    return 0;
}
