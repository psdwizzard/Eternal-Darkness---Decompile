#include "src/game/types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Point6 {
    s16 v[3];
} Point6;

typedef struct Shape {
    Vec3 point;
    unsigned char pad0C[0xC];
    float radius;
    Vec3 axis;
    float tolerance;
    Vec3 bound;
    float bound_radius;
} Shape;

typedef struct Obstacle {
    unsigned char pad00[4];
    Vec3 bound;
    float tolerance;
    Vec3 axis;
    float distance;
} Obstacle;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct Object Object;
typedef struct Entry80201B3C Entry80201B3C;
typedef struct Node80201BD0 Node80201BD0;

typedef void (*PortalCallback)(Point6 *, Point6 *, void *, void *);

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

extern void *fn_80050950(void);
extern int fn_8011EB04(Object *);
extern int fn_8011EB1C(Object *);
extern Obstacle *fn_80143430(const Shape *, Portal *, Result *, Point6 **, Point6 **);
extern void fn_801D7E08(void *value);
extern int fn_80201ADC(void);
extern Entry80201B3C *fn_80201B3C(void);
extern void *fn_80201BC8(void *object);
extern Node80201BD0 *fn_80201BD0(void *object);
extern float fn_80211D4C(const Vec3 *, const Vec3 *);

extern Portal lbl_805B1310[12];
extern s8 lbl_8064D038;
extern float lbl_80650444;

Obstacle *fn_801439E0(const Shape *self, Result *out, void *other, u32 mode) {
    Portal *portal;
    Obstacle *result = NULL;
    void *current;
    void *target;
    void *player;
    float bestDist;
    int i;
    Portal *best;
    int teleport;
    Obstacle *hit;
    Result seg;
    void *object;
    Point6 *edgeA;
    Point6 *edgeB;
    Point6 a;
    Point6 b;
    float dist;
    void *owner;

    if (lbl_8064D038 != 0) {
        object = fn_80201B3C();
        if (object != NULL) {
            current = fn_80201BC8(object);
        } else {
            current = NULL;
        }
        object = (void *)fn_80201ADC();
        if (object != NULL) {
            target = fn_80201BC8(object);
        } else {
            target = NULL;
        }
        player = fn_80050950();
        bestDist = lbl_80650444;
        best = NULL;
        teleport = 0;
        if (other != NULL && fn_8011EB1C(other) == 2) {
            switch (fn_8011EB04(other)) {
            case 0x42:
            case 0x43:
            case 0x44:
                teleport = 1;
                break;
            }
        }

        for (i = 0; i < 12; i++) {
            portal = &lbl_805B1310[i];
            if ((portal->flags & 2) && other != current && other != player) {
                continue;
            }
            owner = portal->owner;
            if (owner == current && other == player) {
                continue;
            }
            if (!(portal->flags & 1)) {
                continue;
            }
            if (other != NULL) {
                if (other == owner) {
                    continue;
                }
                if (other == current && owner == target) {
                    continue;
                }
            }
            hit = fn_80143430(self, portal, &seg, &edgeA, &edgeB);
            if (hit == 0) {
                continue;
            }
            dist = fn_80211D4C(&self->point, &seg.normal);
            if (dist < bestDist) {
                bestDist = dist;
                best = portal;
                result = hit;
                *out = seg;
            }
            if (teleport != 0 && portal->owner != NULL) {
                fn_801D7E08(fn_80201BD0(portal->owner));
            }
        }
        if (teleport != 0) {
            best = NULL;
            result = 0;
        }
        if (best != NULL && best->callback != NULL && !(mode & 8)) {
            b = *edgeB;
            a = *edgeA;
            best->callback(&a, &b, other, best->userData);
        }
    }
    return result;
}
