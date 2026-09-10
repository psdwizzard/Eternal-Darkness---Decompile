typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x2C];
    unsigned char value;
} Entry;

extern Entry* fn_801FD6F4(u32);

int fn_801FEA10(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    int result = -2;
    if (entry != 0) {
        result = entry->value;
    }
    return result;
}
