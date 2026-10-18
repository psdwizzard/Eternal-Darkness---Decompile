#include "src/game/types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Ray { Vec3 origin; u8 pad[12]; Vec3 direction; float limit; } Ray;
typedef struct Object Object;
typedef struct Entry80201B3C Entry80201B3C;

typedef struct Point6 {
    s16 v[3];
} Point6;

typedef struct Plane {
    u8 unk0[0x14];
    Vec3 normal;
    float dist;
} Plane;

typedef void (*PortalCallback)(Point6 *, Point6 *, int, void *);

typedef struct Portal {
    u16 room;
    u8 flags;
    u8 count;
    s16 index;
    u8 pad6[2];
    void *owner;
    PortalCallback callback;
    void *userData;
} Portal;

extern int fn_8011EB1C(Object *);
extern void *fn_8011F130(void *);
extern int fn_8013C7BC(const Vec3 *, const Vec3 *, const Vec3 *, float, float);
extern Plane *fn_80143000(const Ray *, Portal *, Vec3 *, Point6 **, Point6 **);
extern int fn_80201ADC(void);
extern Entry80201B3C *fn_80201B3C(void);
extern void *fn_80201BC8(void *);
extern void PSVECSubtract(const Vec3 *, const Vec3 *, Vec3 *);
extern float PSVECMag(Vec3 *);
extern float PSVECSquareDistance(const Vec3 *, const Vec3 *);

extern Portal lbl_805B1310[12];
extern s8 lbl_8064D038;
extern float lbl_80650440;
extern float lbl_80650444;
extern float lbl_80650448;
extern float lbl_8065044C;

static inline void *get_current(void) {
    Entry80201B3C *entry = fn_80201B3C();
    if (entry != NULL) {
        return fn_80201BC8(entry);
    }
    return NULL;
}

static inline void *get_focus(void) {
    /* The accessor returns the entry address as a 32-bit integer. */
    void *entry = (void *)fn_80201ADC();
    if (entry != NULL) {
        return fn_80201BC8(entry);
    }
    return NULL;
}

static inline int portal_mode(const Vec3 *pos, Vec3 *outPos, void *object, int flags) {
    int mode = (int)object;
    Vec3 delta;

    if (flags & 2) {
        mode = -1;
    } else if (flags & 1) {
        mode = 0;
    } else if (flags & 0x20) {
        float len;
        PSVECSubtract(pos, outPos, &delta);
        len = PSVECMag(&delta);
        if (len < lbl_80650448) {
            mode = -2;
        } else if (len < lbl_8065044C) {
            mode = -3;
        } else {
            mode = -4;
        }
    }
    return mode;
}

Plane *fn_8014317C(const Ray *ray, Vec3 *outPos, Object *object, Vec3 *target, int flags) {
    void *focus;
    void *current;
    Plane *result = NULL;
    Portal *portal;
    int i;
    Portal *best;
    Point6 *bestA;
    Point6 *bestB;
    Plane *plane;
    float bestDist;
    float dist;
    int isFour;
    int ok;
    int mode;
    void *owner;
    Point6 *edgeA;
    Point6 *edgeB;
    Vec3 hit;
    Point6 a;
    Point6 b;

    current = get_current();
    if (lbl_8064D038 != 0) {
        bestDist = lbl_80650444;
        best = NULL;
        focus = get_focus();
        for (i = 0; i < 12; i++) {
            portal = &lbl_805B1310[i];
            isFour = 0;
            if (object != NULL) {
                isFour = fn_8011EB1C(object) == 4;
            }
            if (object != NULL && (portal->flags & 2) && object != current && !isFour) {
                continue;
            }
            if (isFour && portal->owner == focus) {
                continue;
            }
            if (!(portal->flags & 1)) {
                continue;
            }
            if (object != NULL) {
                owner = portal->owner;
                if (object == owner) {
                    continue;
                }
                if (object == current && owner == focus) {
                    continue;
                }
            }
            plane = fn_80143000(ray, portal, &hit, &edgeA, &edgeB);
            if (plane == NULL) {
                continue;
            }
            dist = PSVECSquareDistance(&ray->origin, &hit);
            if (dist < bestDist) {
                bestDist = dist;
                best = portal;
                result = plane;
                *outPos = hit;
                bestA = edgeA;
                bestB = edgeB;
            }
        }
        if (best != NULL && best->callback != NULL && !(flags & 4)) {
            ok = 1;
            if (object != NULL && target != NULL) {
                int side = fn_8013C7BC(fn_8011F130(object), target, &result->normal,
                                       lbl_80650440, result->dist);
                if (side == 1 || side == 0) {
                    ok = 0;
                    result = NULL;
                }
            }
            if (ok) {
                mode = portal_mode(&ray->origin, outPos, object, flags);
                b = *bestB;
                a = *bestA;
                best->callback(&a, &b, mode, best->userData);
            }
        }
    }
    return result;
}
