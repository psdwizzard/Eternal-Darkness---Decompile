typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Entry {
    unsigned char pad00[0x1C];
    u16 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FE96C(u32 id, u16 value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = value;
    }
}
