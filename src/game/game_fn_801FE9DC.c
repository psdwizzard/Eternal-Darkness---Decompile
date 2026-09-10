typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x1E];
    short value;
} Entry;

extern Entry* fn_801FD6F4(u32);

short fn_801FE9DC(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    short result = -2;
    if (entry != 0) {
        result = entry->value;
    }
    return result;
}
