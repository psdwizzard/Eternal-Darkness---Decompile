typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x10];
    u32 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

u32 fn_801FE900(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    u32 result = 0;
    if (entry != 0) {
        result = entry->value;
    }
    return result;
}
