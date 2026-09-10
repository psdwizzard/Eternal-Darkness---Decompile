typedef signed short s16;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x24];
    s16 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FE024(u32 id, s16 value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = value;
    }
}
