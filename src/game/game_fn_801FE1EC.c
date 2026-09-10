typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad00[0x22];
    u16 state;
} Entry;

extern Entry* fn_801FD6F4(u32);

int fn_801FE1EC(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        return entry->state == 2;
    }
    return 0;
}
