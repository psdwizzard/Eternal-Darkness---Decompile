typedef unsigned int u32;

typedef struct Values {
    u32 word[3];
} Values;

typedef struct Entry {
    unsigned char pad00[0x48];
    Values values;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FE890(u32 id, const Values* values)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->values = *values;
    }
}
