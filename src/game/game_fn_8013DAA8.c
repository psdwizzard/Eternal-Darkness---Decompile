typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Entry { void* resource; unsigned char index; unsigned char pad[3]; } Entry;
typedef struct Group {
    unsigned char pad0[0x3C];
    unsigned short count;
    unsigned short pad3E;
    Entry* entries;
    unsigned char* records;
    unsigned char pad48[4];
    const void* context;
} Group;

extern void* lbl_8064C4E0;
extern float lbl_80650354;
extern int fn_801E79FC(void*, int);
extern int fn_8013D998(const Vec3*, const void*, const void*, Vec3*);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);

Entry* fn_8013DAA8(const Vec3* point, const Group* group, Vec3* result)
{
    unsigned short i;
    float best = lbl_80650354;
    Entry* entry = group->entries;
    const void* context = group->context;
    Entry* found = 0;
    Vec3 candidate;
    i = 0;

    while (i < group->count) {
        if (fn_801E79FC(lbl_8064C4E0, (int)entry->resource) &&
            fn_8013D998(point, group->records + entry->index * 56,
                        context, &candidate)) {
            float distance = PSVECSquareDistance(&candidate, point);
            if (distance < best) {
                best = distance;
                found = entry;
                *result = candidate;
            }
        }
        i++;
        entry++;
    }
    return found;
}
