typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Entry { u8 pad00[0x70]; unsigned short value; } Entry;
extern Entry* fn_801FD6F4(u32);
int fn_801FE52C(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    int result = 0;
    if (entry != 0) result = entry->value == 1;
    return result;
}
