typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x20];
    s16 step;
    unsigned char pad22[0x32];
    u16 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

int fn_801FE0B4(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    int result = 0;
    if (entry != 0) {
        entry->value -= entry->step;
        if (entry->value < entry->step) {
            entry->value = 1;
            result = 1;
        }
    }
    return result;
}
