typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Entry { u8 pad00[0x70]; unsigned short value; } Entry;
extern Entry* fn_801FD6F4(u32);
void fn_801FE4FC(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) entry->value = 1;
}
