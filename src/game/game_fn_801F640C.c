typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Owner {
    unsigned char pad_0[0x12];
    u16 count;
    void* entries;
    unsigned char pad_18[0x812A];
    signed char enabled;
    signed char ready;
} Owner;

extern Owner* fn_8015C28C(int);
extern void fn_801F5EFC(u32, u32, u32, u16, void*);

void fn_801F640C(u32 first, u32 second, u32 third)
{
    int i;

    for (i = 0; i < 2; i++) {
        Owner* owner = fn_8015C28C(i);
        if (owner != 0 && owner->enabled != 0 && owner->ready != 0) {
            fn_801F5EFC(first, second, third, owner->count, owner->entries);
        }
    }
}
