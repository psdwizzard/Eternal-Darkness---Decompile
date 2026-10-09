typedef unsigned char u8;
typedef signed int s32;

typedef struct ObjectState {
    u8 pad[0x9F];
    u8 kind;
} ObjectState;

extern void *fn_80201B8C(void *object);

s32 fn_8003BF5C(void *object)
{
    ObjectState *state;

    if (object != 0 && (state = fn_80201B8C(object)) != 0) {
        switch (state->kind) {
        case 31:
        case 32:
        case 33:
        case 35:
        case 36:
        case 40:
            return 1;
        }
    }
    return 0;
}
