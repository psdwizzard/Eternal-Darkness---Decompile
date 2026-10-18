#include "src/game/types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Segment { Vec3 start, end, direction; float distance; } Segment;
typedef Segment Ray;
typedef struct Object Object;
typedef struct Entry80201B3C Entry80201B3C;

typedef struct Point6 {
    struct { s16 x, y; } xy;
    union { s16 value; u16 bits; } z;
} Point6;

typedef struct EdgeSet {
    Point6 points[4];
} EdgeSet;

typedef struct Plane {
    u8 unk0[0x14];
    Vec3 normal;
    float offset;
} Plane;

typedef struct PlanePair {
    Plane front;
    u8 pad24[0x14];
    Plane back;
    u8 pad5C[0x14];
} PlanePair;

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

typedef struct PortalTable {
    Portal portals[12];
    PlanePair planes[12][7];
    EdgeSet edges[12][7];
} PortalTable;

extern void *fn_80050950(void);
extern int fn_8011EB04(Object *);
extern int fn_8011EB1C(Object *);
extern int fn_8013D998(const Ray *, const struct Plane *, const void *, Vec3 *);
extern void fn_801435DC(Vec3 *, Vec3 *, Segment *);
extern int fn_80201ADC(void);
extern Entry80201B3C *fn_80201B3C(void);
extern void *fn_80201BC8(void *);
extern float fn_80211B44(const Vec3 *, const Vec3 *);

extern PortalTable lbl_805B1310;
extern s8 lbl_8064D038;
extern s32 lbl_8064D18C;
extern float lbl_80650444;

PlanePair *fn_801436E0(void *self, void *other, int notify) {
    register PortalTable *table;
    PlanePair *result = NULL;
    int searching = 1;
    int blocked;
    Segment selfBuf;
    Segment otherBuf;
    Vec3 scratch;
    Point6 b;
    Point6 a;

    register Portal *portal;
    Point6 *bestPoint;
    PlanePair *best;
    EdgeSet *bestEdges;
    int i;
    int j;
    int selfHits;
    int otherHits;

    table = &lbl_805B1310;
    blocked = 0;
    selfHits = 0;
    otherHits = 0;
    if (fn_8011EB1C(self) == 2) {
        switch (fn_8011EB04(self)) {
        case 0x42:
        case 0x43:
        case 0x44:
            blocked = 1;
            break;
        }
    }
    if (lbl_8064D038 != 0 && blocked == 0) {
        fn_801435DC(self, other, &selfBuf);
        fn_801435DC(other, self, &otherBuf);

        /* ASM: addi retains the zero-offset table-member address calculation;
         * the compiler folds this member address to a register move in C. */
        asm { addi portal, table, 0 }
        for (i = 0; searching != 0 && i < 12; portal++, i++) {
            void *current;
            void *owner;
            float bestDist;
            void *target;
            void *player;
            struct { PlanePair (*planes)[7]; EdgeSet (*edgeSets)[7]; } arrays;

            if ((current = fn_80201B3C()) != NULL) {
                current = fn_80201BC8(current);
            } else {
                current = NULL;
            }
            player = fn_80050950();
            if ((target = (void *)fn_80201ADC()) != NULL) {
                target = fn_80201BC8(target);
            } else {
                target = NULL;
            }

            if ((portal->flags & 2) && self != current && self != player) {
                continue;
            }
            owner = portal->owner;
            if (owner == current && self == player) {
                continue;
            }
            if (!(portal->flags & 1)) {
                continue;
            }
            if (portal->room != lbl_8064D18C) {
                continue;
            }
            if (self == owner) {
                continue;
            }
            if (self == current && owner == target) {
                continue;
            }

            bestDist = lbl_80650444;
            bestEdges = NULL;
            bestPoint = NULL;
            best = NULL;
            arrays.edgeSets = NULL;
            arrays.planes = table->planes;
            arrays.edgeSets = table->edges;
            for (j = 0; j < portal->count; j++) {
                PlanePair *plane = &arrays.planes[portal->index][j];
                EdgeSet *edges = &arrays.edgeSets[portal->index][j];
                struct Plane *back = &plane->back;
                float dist;
                int hits;

                hits = fn_8013D998(&selfBuf, &plane->front, edges, &scratch);
                hits += fn_8013D998(&selfBuf, back, edges, &scratch);
                selfHits += hits;
                hits = fn_8013D998(&otherBuf, &plane->front, edges, &scratch);
                hits += fn_8013D998(&otherBuf, back, edges, &scratch);
                otherHits += hits;
                dist = -(plane->front.offset + fn_80211B44(&plane->front.normal, &selfBuf.start));
                if (dist < bestDist) {
                    bestDist = dist;
                    best = plane;
                    bestEdges = edges;
                    bestPoint = &edges->points[3];
                }
            }

            if (((selfHits & 1) && !(otherHits & 1)) ||
                (!(selfHits & 1) && (otherHits & 1))) {
                result = best;
                searching = 0;
                if (notify != 0 && portal->callback != NULL) {
                    void *userData;
                    a.xy = bestPoint->xy;
                    userData = portal->userData;
                    a.z.bits = bestPoint->z.bits;
                    b = bestEdges->points[0];
                    portal->callback(&b, &a, 0, userData);
                }
            }
        }
    }
    return result;
}
