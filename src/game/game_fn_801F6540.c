typedef unsigned short u16;

typedef struct Owner {
    unsigned char pad_0[0x12];
    u16 count;
    unsigned char pad_14[0x812E];
    signed char enabled;
    signed char ready;
} Owner;

extern Owner* fn_8015C28C(int);

void fn_801F6540(void)
{
    Owner* owner = fn_8015C28C(2);

    if (owner != 0 && owner->enabled != 0 && owner->ready != 0) {
        u16 i;
        for (i = 0; i < owner->count; i++) {
        }
    }
}
