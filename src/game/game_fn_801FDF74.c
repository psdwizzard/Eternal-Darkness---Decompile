typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x20];
    s16 step;
    unsigned char pad22[0x22];
    s32 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FDF74(u32 id, s32 value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = value;
        entry->step = value >> 5;
    }
}
