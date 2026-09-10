typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[0x26];
    u16 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FD848(u32 id, u16 value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = value;
    }
}
