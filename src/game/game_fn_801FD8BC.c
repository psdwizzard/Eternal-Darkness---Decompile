typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[0x40];
    u32 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

u32 fn_801FD8BC(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        return entry->value;
    }
    return 0;
}
