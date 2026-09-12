typedef unsigned int u32;

typedef struct Object80201CDC Object80201CDC;
typedef struct Object80201CDCState Object80201CDCState;

struct Object80201CDCState {
    unsigned char padding[8];
    u32 value;
};

struct Object80201CDC {
    unsigned char padding[0x24];
    Object80201CDCState *state;
};

u32 fn_80201CDC(Object80201CDC *object)
{
    return object->state->value;
}
