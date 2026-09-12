typedef unsigned int u32;

typedef struct Object80201CE8 Object80201CE8;
typedef struct Object80201CE8State Object80201CE8State;

struct Object80201CE8State {
    unsigned char padding[8];
    u32 flags;
};

struct Object80201CE8 {
    unsigned char padding[0x24];
    Object80201CE8State *state;
};

void fn_80201CE8(Object80201CE8 *object, u32 clear, u32 set)
{
    object->state->flags &= ~clear;
    object->state->flags |= set;
}
