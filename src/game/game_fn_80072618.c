#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Spot {
    u8 pad0[0x2c];
    Vec3s pos;
    u8 pad32[0x48 - 0x32];
    u32 flags;
} Spot;

typedef struct SpotTable {
    u8 pad0[0x34];
    u16 count;
    u16 pad36;
    const Spot *spots;
} SpotTable;

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

typedef struct Owner Owner;
typedef struct Object80201EB8 Object80201EB8;

extern u32 fn_800FBFB0(void);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_80201B4C(int *);
extern void fn_8013F3C0(Shape *, const Vec3 *, const Vec3 *, float);
extern void *fn_8013FBE4(Owner *, const void *, Result *, void *, u32);
extern void *fn_8015C2FC(int);
extern void *fn_8015C390(int);
extern u32 fn_80178E94(const float *, const float *);
extern u32 fn_80178F14(int, int, int, int, int, int);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(Object80201EB8 *);
extern int lbl_8064D18C;
extern float lbl_8064E858;
extern float lbl_8064E85C;

int fn_80072618(Vec3 *origin, Vec3 *out, int radius, int flags)
{
    SpotTable *table;
    register u32 mask;
    register u32 negative;
    Shape shape;
    Result hit;
    Vec3 candidatePos;
    const Spot *sampled;
    Vec3 *object;
    Vec3 randomPos;
    u32 randomDistance;
    Vec3 nearbyPos;
    register u32 nearest;
    Vec3 objectPos;
    const Spot *found = NULL;
    int i;
    register int success;
    const Spot *spot;
    u32 bestDistance;
    u32 distance;
    int tries;
    Object80201EB8 *node;
    int blockers;
    Owner *filter;

    table = fn_8015C390(2);
    nearest = flags & 1U;
    /* Nearest starts at the maximum distance; farthest starts at zero. */
    /* ASM: li, li, neg, and initialize success and the distance mask.
       Equivalent C swaps the mask and negation registers; keeping the
       initializers together also preserves the retail instruction order. */
    asm {
        li mask, -1
        li success, 0
        neg negative, nearest
        and mask, mask, negative
    }
    bestDistance = mask;
    if (table != NULL && table->count != 0) {
        spot = table->spots;
        /* Sample a bounded number of random spots. */
        if (flags & 4U) {
            for (tries = 0; tries < table->count * 2 && found == NULL; tries++) {
                sampled = &spot[(int)fn_800FBFB0() % table->count];
                randomPos.x = (float)sampled->pos.x;
                randomPos.y = (float)sampled->pos.y;
                randomPos.z = (float)sampled->pos.z;
                randomDistance = fn_80178E94(&origin->x, &randomPos.x);
                if ((sampled->flags & 0x40) &&
                    ((u32)radius == 0U || (randomDistance < radius && randomDistance > 100))) {
                    if (flags & 0x100U) {
                        float adjustment;
                        float width;
                        float value;
                        filter = fn_8015C2FC(2);
                        value = origin->z;
                        adjustment = lbl_8064E858;
                        width = lbl_8064E85C;
                        value = value + adjustment;
                        origin->z = value;
                        value = randomPos.z;
                        randomPos.z = value + adjustment;
                        fn_8013F3C0(&shape, origin, &randomPos, width);
                        if (fn_8013FBE4(filter, &shape, &hit, 0, 8) != NULL)
                            found = sampled;
                        value = origin->z;
                        adjustment = lbl_8064E858;
                        origin->z = value - adjustment;
                        value = randomPos.z;
                        randomPos.z = value - adjustment;
                    } else {
                        found = sampled;
                    }
                }
            }
        } else {
            /* Compare each spot and reject ones occupied by nearby objects. */
            for (i = 0; i < table->count; i++, spot++) {
                if (!(spot->flags & 0x40))
                    continue;
                candidatePos.x = (float)spot->pos.x;
                candidatePos.y = (float)spot->pos.y;
                candidatePos.z = (float)spot->pos.z;
                distance = fn_80178F14((int)candidatePos.x, (int)candidatePos.y,
                                      (int)candidatePos.z, (int)origin->x,
                                      (int)origin->y, (int)origin->z);
                if ((nearest && distance < bestDistance) ||
                    ((flags & 2U) && distance > bestDistance)) {
                    node = fn_80201B9C();
                    blockers = 0;
                    while (node != NULL && blockers == 0) {
                        object = fn_80201BC8(node);
                        if (object != NULL) {
                            fn_8011F114(&objectPos, object);
                            nearbyPos = objectPos;
                            {
                                int room = fn_80201EB8(node);
                                int kind = fn_80201B4C((int *)node);
                                if (lbl_8064D18C == room &&
                                    fn_80178E94(&candidatePos.x, &nearbyPos.x) < radius &&
                                    ((u32)kind <= 1 || kind == 2))
                                    blockers++;
                            }
                        }
                        node = fn_80201BC0(node);
                    }
                    if (blockers == 0) {
                        bestDistance = distance;
                        found = spot;
                    }
                }
            }
        }
    }
    if (found != NULL) {
        success = 1;
        out->x = (float)found->pos.x;
        out->y = (float)found->pos.y;
        out->z = (float)found->pos.z;
    }
    return success;
}
