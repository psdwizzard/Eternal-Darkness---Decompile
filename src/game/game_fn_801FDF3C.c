typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x14];
    s32 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FDF3C(u32 id, s32 value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = value;
    }
}
