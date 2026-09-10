typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Entry { u8 pad00[0x74]; u32 value; } Entry;
extern Entry* fn_801FD6F4(u32);
u32 fn_801FE494(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    u32 result = -1;
    if (entry != 0) result = entry->value;
    return result;
}
