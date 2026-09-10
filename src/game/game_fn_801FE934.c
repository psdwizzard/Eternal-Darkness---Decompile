typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x2C];
    u8 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FE934(u32 id, u8 value)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = value;
    }
}
