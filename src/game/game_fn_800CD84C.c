typedef unsigned char u8;

typedef struct Resource {
    u8 pad[0x2C];
    int slots[3];
} Resource;

typedef struct RuntimeState {
    u8 pad[0x8C];
    volatile Resource * volatile resource;
} RuntimeState;

extern void *fn_80201B8C();

#pragma opt_lifetimes off

int fn_800CD84C(void *object)
{
    int count = 0;

    if (object != 0) {
        RuntimeState *state = ((RuntimeState *)fn_80201B8C(object));
        volatile Resource *resource;
        resource = state->resource;
        if (resource->slots[0] != 0) {
            count = 1;
        }
        resource = state->resource;
        if (resource->slots[1] != 0) {
            count++;
        }
        resource = state->resource;
        if (resource->slots[2] != 0) {
            count++;
        }
    }
    return count;
}

#pragma opt_lifetimes reset
