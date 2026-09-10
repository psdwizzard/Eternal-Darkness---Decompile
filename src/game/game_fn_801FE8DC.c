typedef unsigned short u16;

typedef struct Entry {
    unsigned char pad00[0x2A];
    u16 flags;
    unsigned char pad2C[0xC];
    float x;
    float y;
    float z;
} Entry;

void fn_801FE8DC(Entry* entry, float x, float y, float z)
{
    if (entry != 0) {
        entry->flags |= 1;
        entry->x = x;
        entry->y = y;
        entry->z = z;
    }
}
