typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[0x3C];
    u32 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FD80C(u32 id, const u32* value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = *value;
    }
}
