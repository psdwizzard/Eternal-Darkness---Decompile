typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Owner {
    unsigned char pad_0[0x18];
    u16 count;
    unsigned char pad_1A[2];
    void* entries;
    unsigned char pad_20[0x8122];
    signed char enabled;
    signed char ready;
} Owner;

extern Owner* fn_8015C28C(int);
extern void fn_801F62D0(u32, u16, void*, u16);

void fn_801F6370(u32 key, u16 value)
{
    Owner* owner = fn_8015C28C(2);
    if (owner != 0 && owner->enabled != 0 && owner->ready != 0) {
        fn_801F62D0(key, value, owner->entries, owner->count);
    }
}
