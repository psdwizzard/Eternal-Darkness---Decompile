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
    Spot *spots;
} SpotTable;

typedef struct Shape {
    u8 data[0x40];
} Shape;

typedef struct Hit {
    u8 data[0x18];
} Hit;

extern int fn_800FBFB0(void);
extern void fn_8011F114(Vec3 *, void *);
extern u32 fn_8011FAEC(void *);
extern void fn_8013F3C0(Shape *, Vec3 *, Vec3 *, float);
extern void *fn_8013FBE4(void *, Shape *, Hit *, int, int);
extern void *fn_8015C2FC(int);
extern SpotTable *fn_8015C390(int);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern u32 fn_80178F14(int, int, int, int, int, int);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(void *);
extern int lbl_8064D18C;
extern float lbl_8064E858;
extern float lbl_8064E85C;

int fn_80072A2C(Vec3 *origin, Vec3 *out, u32 radius, u32 flags)
{
    /* Select an all-bits distance limit when nearest mode is enabled. */
    u32 mask = -1;
    Shape shape;
    Hit hit;
    Vec3 candidatePos;
    Vec3 randomPos;
    Vec3 nearbyPos;
    Vec3 objectPos;
    void *filter;
    u32 distance;
    Spot *found = NULL;
    Spot *sampled;
    int i;
    void *node;
    u32 bestDistance;
    u32 nearest;
    int success;
    SpotTable *table;
    Spot *spot;
    int blockers;
    void *object;

    table = fn_8015C390(2);
    nearest = flags & 1;
    success = 0;
    bestDistance = -nearest & mask;
    if (table != NULL && table->count != 0) {
        spot = table->spots;
        /* Sample a bounded number of random spots. */
        if (flags & 4) {
            for (i = 0; i < table->count * 2 && found == NULL; i++) {
                sampled = &spot[(fn_800FBFB0() % table->count)];
                randomPos.x = (float)sampled->pos.x;
                randomPos.y = (float)sampled->pos.y;
                randomPos.z = (float)sampled->pos.z;
                distance = fn_80178E94(origin, &randomPos);
                if ((sampled->flags & 0x40) &&
                    (radius == 0 || (distance < radius && distance > 100))) {
                    if (flags & 0x100) {
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
                        if (fn_8013FBE4(filter, &shape, &hit, 0, 0) != NULL)
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
                    ((flags & 2) && distance > bestDistance)) {
                    node = fn_80201B9C();
                    blockers = 0;
                    while (node != NULL && blockers == 0) {
                        object = fn_80201BC8(node);
                        if (object != NULL) {
                            fn_8011F114(&objectPos, object);
                            nearbyPos = objectPos;
                            {
                                int room = fn_80201EB8(node);
                                u32 objectFlags;
                                if (object != NULL)
                                    objectFlags = fn_8011FAEC(object);
                                else
                                    objectFlags = 0;
                                if (lbl_8064D18C == room &&
                                    fn_80178E94(&candidatePos, &nearbyPos) < radius &&
                                    (objectFlags & 0xc0))
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
