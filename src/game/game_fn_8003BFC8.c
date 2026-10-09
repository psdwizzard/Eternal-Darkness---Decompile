typedef unsigned char u8;
typedef signed int s32;

typedef struct ObjectState {
    u8 pad[0x9F];
    u8 kind;
} ObjectState;

extern void *fn_80201B8C(void *object);

s32 fn_8003BFC8(void *object)
{
    ObjectState *state;
    s32 result = 0;

    state = object != 0 ? fn_80201B8C(object) : 0;
    if (state != 0) {
        switch (state->kind) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
        case 11:
        case 24:
            result = 1;
            break;
        }
    }
    return result;
}
