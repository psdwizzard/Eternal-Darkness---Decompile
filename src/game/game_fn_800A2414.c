typedef unsigned char u8;
#pragma enumsalwaysint off

typedef enum State800A2414 {
    STATE_800A2414_ZERO,
    STATE_800A2414_ONE,
    STATE_800A2414_FORCE_SHORT = 0x100
} State800A2414;

typedef struct Object800A2414 {
    u8 pad000[0x86];
    State800A2414 state;
    u8 pad088[0x1FA];
    u8 count;
} Object800A2414;

void fn_800A2414(Object800A2414* object)
{
    if ((int)object->state == 1) {
        object->count--;
    }
}
