typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Owner {
    unsigned char pad_0[0x12];
    u16 count;
    void* animations;
    unsigned char pad_18[0x812A];
    signed char enabled;
    signed char ready;
} Owner;

extern Owner* fn_8015C28C(int);
extern int fn_801F5F98(u32, u32, u16, u16, void*);

#pragma use_lmw_stmw on

int fn_801F6198(u32 key, u32 clear, u16 set)
{
    int i;
    int matches = 0;

    for (i = 0; i < 2; i++) {
        Owner* owner = fn_8015C28C(i);
        if (owner != 0 && owner->enabled != 0 && owner->ready != 0) {
            matches += fn_801F5F98(key, clear, set, owner->count, owner->animations);
        }
    }
    return matches;
}
