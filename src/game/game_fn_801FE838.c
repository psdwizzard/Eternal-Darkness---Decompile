typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x60];
    float x;
    float y;
    float z;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FE838(u32 id, float x, float y, float z)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->x = x;
        entry->y = y;
        entry->z = z;
    }
}
