typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[4];
    s32 range;
    s32 period;
    unsigned char pad10[0xE];
    s16 divisor;
    unsigned char pad20[6];
    s16 adjustment;
} Entry;

extern Entry* fn_801FD6F4(u32);
extern u32 fn_8015C910(void);

void fn_801FDDB0(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0 && fn_8015C910() == 0 && entry->divisor != 0 &&
        entry->adjustment % entry->divisor == 0) {
        entry->range--;
        entry->period--;
    }
}
