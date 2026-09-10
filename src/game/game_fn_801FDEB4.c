typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Entry {
    unsigned char pad00[0x34];
    Vec3 position;
} Entry;

extern Entry* fn_801FD6F4(u32);

void fn_801FDEB4(u32 id, const Vec3* position)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->position.x = position->x;
        entry->position.y = position->y;
        entry->position.z = position->z;
    }
}
