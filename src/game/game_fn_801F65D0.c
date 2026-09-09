typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Owner {
    unsigned char pad_0[0x18];
    u16 value;
    unsigned char pad_1A[2];
    u32 key;
    unsigned char pad_20[0x8122];
    signed char enabled;
    signed char ready;
} Owner;

extern Owner* fn_8015C28C(int);
extern void fn_801F5D40(u32, u16);

void fn_801F65D0(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        Owner* owner = fn_8015C28C(i);
        if (owner != 0 && owner->enabled != 0 && owner->ready != 0) {
            fn_801F5D40(owner->key, owner->value);
        }
    }
}
