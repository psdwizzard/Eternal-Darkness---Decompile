#pragma use_lmw_stmw on

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Owner {
    unsigned char pad0[0xC];
    void* context;
    unsigned char pad10[0x34];
    unsigned short count;
    unsigned char pad46[2];
    unsigned char* entries;
} Owner;

extern float lbl_806503D8;
extern int fn_8013D998(const Vec3*, const void*, void*, Vec3*);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern void fn_80140AEC(void*, Owner*);

void* fn_8013FF44(Owner* owner, const Vec3* value, Vec3* out)
{
    Vec3 candidate;
    unsigned char* entry;
    int count;
    unsigned char* geometry;
    int index;
    void* result;
    float best;

    best = lbl_806503D8;
    geometry = owner->context;
    entry = owner->entries;
    count = owner->count;
    result = 0;
    index = 0;
    while (index < count) {
        if (fn_8013D998(value, entry, geometry, &candidate)) {
            float distance = PSVECSquareDistance(&candidate, value);
            if (distance < best) {
                best = distance;
                result = entry;
                *out = candidate;
                fn_80140AEC(entry, owner);
            }
        }
        entry += 0x38;
        index++;
    }
    return result;
}
