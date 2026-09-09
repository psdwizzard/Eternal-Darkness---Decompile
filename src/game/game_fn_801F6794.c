typedef unsigned short u16;

typedef struct Entry {
    unsigned char data[0xC];
} Entry;

typedef struct Owner {
    unsigned char pad_0[0x18];
    u16 count;
    unsigned char pad_1A[2];
    Entry* entries;
    unsigned char pad_20[0x8122];
    signed char enabled;
    signed char ready;
} Owner;

extern Owner* fn_8015C28C(int);
extern int fn_801F6734(void*, Entry*);

#pragma use_lmw_stmw on

int fn_801F6794(void* source)
{
    int size = 0;
    int i;

    for (i = 0; i < 2; i++) {
        Owner* owner = fn_8015C28C(i);
        if (owner != 0 && owner->enabled != 0 && owner->ready != 0) {
            int j;
            for (j = 0; j < owner->count; j++) {
                size += fn_801F6734((unsigned char*)source + (u16)size,
                                    &owner->entries[j]);
            }
        }
    }
    return (u16)(size + 31) & ~31;
}
