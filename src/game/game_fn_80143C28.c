#include "src/game/types.h"

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Surface {
    Vec3 point;
    float pad0C;
    float pad10;
    Vec3 normal;
    float extent;
} Surface;
typedef struct SurfaceEntry {
    Surface surface;
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
extern int fn_8013F078(const Vec3 *, const Surface *, const void *, Result *, float);
extern float PSVECSquareDistance(const Vec3 *, const Vec3 *);

Surface *fn_80143C28(const Vec3 *point, Portal *portal, Result *out,
                    Point6 **edgeA, Point6 **edgeB, float extra)
{
    Result result;
    Surface *best = 0;
    Surface *front;
    Surface *back;
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
            if (fn_8013F078(point, front, bounds, &result, extra)) {
                dist = PSVECSquareDistance(&result.normal, point);
                if (dist < bestDist) {
                    *edgeA = &bounds->corners[0];
                    bestDist = dist;
                    best = front;
                    *edgeB = &bounds->corners[3];
                    *out = result;
                }
            } else if (fn_8013F078(point, back, bounds, &result, extra)) {
                dist = PSVECSquareDistance(&result.normal, point);
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
