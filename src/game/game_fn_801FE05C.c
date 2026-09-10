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

int fn_801FE05C(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    int result = 0;
    if (entry != 0) {
        entry->value -= entry->step;
        if (entry->value <= 0) {
            entry->value = 0;
            result = 1;
        }
    }
    return result;
}
