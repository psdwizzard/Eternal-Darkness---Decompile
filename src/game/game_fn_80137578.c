typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct CollisionEntry {
    unsigned int condition;
    unsigned char obstacle_index;
    unsigned char flags;
} CollisionEntry;

typedef struct CollisionWorld {
    unsigned char pad00[0x3C];
    unsigned short entry_count;
    CollisionEntry* entries;
    unsigned char* obstacles;
    unsigned char pad48[4];
    void* context;
} CollisionWorld;

extern int fn_801374D8(void* object, const Shape* shape,
                       const CollisionEntry* entry,
                       const CollisionWorld* world, Result* result);
extern float fn_80211D4C(const Vec3* a, const Vec3* b);
extern float lbl_80650278;

const CollisionEntry* fn_80137578(void* object, const Shape* shape,
                                  const CollisionWorld* world, Result* result)
{
    Result candidate;
    unsigned short i;
    const CollisionEntry* entry;
    const CollisionEntry* closest;
    float best;

    best = lbl_80650278;
    entry = world->entries;
    closest = 0;

    for (i = 0; i < world->entry_count; i++, entry++) {
        if (fn_801374D8(object, shape, entry, world, &candidate)) {
            float distance = fn_80211D4C(&candidate.normal, &shape->first);
            if (distance < best) {
                best = distance;
                closest = entry;
                *result = candidate;
            }
        }
    }
    return closest;
}
