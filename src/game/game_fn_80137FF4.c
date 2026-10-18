typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Entry {
    unsigned int flags;
    int id;
    void* owner;
    Vec3 position;
    float radius;
} Entry;

typedef struct Capsule {
    Vec3 point;
    Vec3 other;
    float radius;
    Vec3 axis;
    float limit;
    Vec3 bound;
    float bound_radius;
} Capsule;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

extern Entry lbl_805ADE20[15];
extern float lbl_806502A0;
extern int fn_8013E714(const Capsule*, const Vec3*, Result*, float);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);

int fn_80137FF4(void* owner, const Capsule* shape, Result* result)
{
    Result candidate;
    float best;
    int found;
    int i;
    Entry* entry;

    best = lbl_806502A0;
    entry = lbl_805ADE20;
    found = 0;
    i = 0;
    do {
        if ((entry->flags & 1) && owner != entry->owner &&
            fn_8013E714(shape, &entry->position, &candidate, entry->radius)) {
            float distance = PSVECSquareDistance(&candidate.normal, &shape->point);
            if (distance < best) {
                best = distance;
                found = 1;
                *result = candidate;
            }
        }
        i++;
        entry++;
    } while (i < 15);
    return found;
}
