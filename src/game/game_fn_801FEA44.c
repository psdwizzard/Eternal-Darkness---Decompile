typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x20];
    short value;
    unsigned char pad22[0x22];
    int amount;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FEA44(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value = entry->amount >> 5;
        if (entry->value == 0) {
            entry->value = 1;
        }
    }
}
