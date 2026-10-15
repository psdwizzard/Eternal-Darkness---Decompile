#include "src/game/types.h"

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Ray { Vec3 origin; u8 pad[12]; Vec3 direction; float limit; } Ray;
typedef struct Point6 { s16 v[3]; } Point6;
typedef struct Plane {
    u8 pad[0x14];
    Vec3 normal;
    float offset;
} Plane;
typedef struct Portal {
    u16 room;
    u8 flags;
    u8 count;
    s16 index;
    u8 pad6[2];
    void *owner;
    void (*callback)(Point6 *, Point6 *, int, void *);
    void *userData;
} Portal;

typedef struct PlanePair {
    Plane first;
    u8 pad24[0x14];
    Plane second;
    u8 pad5C[0x14];
} PlanePair;
typedef struct Quad { Point6 point[4]; } Quad;

extern int fn_8013D998(const Ray *, const Plane *, const void *, Vec3 *);
extern float fn_80211D4C(const Vec3 *, const Vec3 *);
extern PlanePair lbl_805B1400[][7];
extern Quad lbl_805B38C0[][7];
extern s32 lbl_8064D18C;
extern float lbl_80650444;

Plane *fn_80143000(const Ray *ray, Portal *portal, Vec3 *out,
                   Point6 **edgeA, Point6 **edgeB)
{
    Vec3 hit;
    Plane *result = 0;
    s16 i;
    float bestDistance;
    Plane *first;
    Plane *second;
    Point6 *points;
    float distance;

    if (portal->room == lbl_8064D18C) {
        bestDistance = lbl_80650444;
        for (i = 0; i < portal->count; i++) {
            first = &lbl_805B1400[portal->index][i].first;
            points = lbl_805B38C0[portal->index][i].point;
            second = &lbl_805B1400[portal->index][i].second;
            if (fn_8013D998(ray, first, points, &hit)) {
                distance = fn_80211D4C(&hit, &ray->origin);
                if (distance < bestDistance) {
                    *edgeA = points;
                    bestDistance = distance;
                    result = first;
                    *edgeB = points + 3;
                    *out = hit;
                }
            } else if (fn_8013D998(ray, second, points, &hit)) {
                distance = fn_80211D4C(&hit, &ray->origin);
                if (distance < bestDistance) {
                    *edgeA = points;
                    bestDistance = distance;
                    result = second;
                    *edgeB = points + 3;
                    *out = hit;
                }
            }
        }
    }
    return result;
}
