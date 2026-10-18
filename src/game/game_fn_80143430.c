#include "src/game/types.h"

typedef struct Vec3 { float x, y, z; } Vec3;
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
typedef struct SurfaceEntry {
    Obstacle surface;
    u8 pad24[0x14];
} SurfaceEntry;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Point6 { s16 v[3]; } Point6;
typedef struct PortalBounds { Point6 corners[4]; } PortalBounds;
typedef struct Portal {
    u16 room;
    u8 flags;
    u8 count;
    s16 index;
    u8 pad6[2];
    void *owner;
    void (*callback)(Point6 *, Point6 *, void *, void *);
    void *userData;
} Portal;

extern SurfaceEntry lbl_805B1400[12][7][2];
extern PortalBounds lbl_805B38C0[12][7];
extern int lbl_8064D18C;
extern float lbl_80650444;
extern int fn_8013E284(const Shape *, const Obstacle *, const void *, Result *);
extern float PSVECSquareDistance(const Vec3 *, const Vec3 *);

Obstacle *fn_80143430(const Shape *shape, Portal *portal, Result *out,
                    Point6 **edgeA, Point6 **edgeB)
{
    Result result;
    Obstacle *best = 0;
    Obstacle *front;
    Obstacle *back;
    PortalBounds *bounds;
    float bestDist;
    float dist;
    s16 i;

    if (portal->room == lbl_8064D18C) {
        bestDist = lbl_80650444;
        for (i = 0; i < portal->count; i++) {
            front = &lbl_805B1400[portal->index][i][0].surface;
            bounds = &lbl_805B38C0[portal->index][i];
            back = &lbl_805B1400[portal->index][i][1].surface;
            if (fn_8013E284(shape, front, bounds, &result)) {
                dist = PSVECSquareDistance(&result.normal, &shape->point);
                if (dist < bestDist) {
                    *edgeA = &bounds->corners[0];
                    bestDist = dist;
                    best = front;
                    *edgeB = &bounds->corners[3];
                    *out = result;
                }
            } else if (fn_8013E284(shape, back, bounds, &result)) {
                dist = PSVECSquareDistance(&result.normal, &shape->point);
                if (dist < bestDist) {
                    *edgeA = &bounds->corners[0];
                    bestDist = dist;
                    best = back;
                    *edgeB = &bounds->corners[3];
                    *out = result;
                }
            }
        }
    }
    return best;
}
