#include "src/game/types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Point6 {
    s16 v[3];
} Point6;

typedef struct EdgeSet {
    Point6 points[4];
} EdgeSet;

typedef struct Plane {
    u8 unk0[0x14];
    Vec3 normal;
    float dist;
    u8 unk24[0x14];
    u8 unk38[0x38];
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

typedef struct PortalTable {
    Portal portals[12];
    Plane planes[12][7];
    EdgeSet edges[12][7];
} PortalTable;

extern void *fn_80050950(void);
extern int fn_8011EB04(void *);
extern int fn_8011EB1C(void *);
extern int fn_8013D998(void *, void *, EdgeSet *, void *);
extern void fn_801435DC(void *, void *, void *);
extern void *fn_80201ADC(void);
extern void *fn_80201B3C(void);
extern void *fn_80201BC8();
extern float fn_80211B44(const Vec3 *, const Vec3 *);

extern PortalTable lbl_805B1310;
extern s8 lbl_8064D038;
extern s32 lbl_8064D18C;
extern float lbl_80650444;

Plane *fn_801436E0(void *self, void *other, int notify) {
    PortalTable *table;
    Plane *result = NULL;
    int searching = 1;
    int blocked;
    int selfHits;
    int otherHits;
    u8 selfBuf[0x28];
    u8 otherBuf[0x28];
    u8 scratch[0xC];
    Point6 b;
    Point6 a;
    Portal *portal;
    int i;

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
        fn_801435DC(self, other, selfBuf);
        fn_801435DC(other, self, otherBuf);

        portal = &table->portals[0];
        for (i = 0; searching != 0 && i < 12; portal++, i++) {
            void *current;
            void *player;
            void *target;
            void *owner;
            Plane *best;
            EdgeSet *bestEdges;
            Point6 *bestPoint;
            float bestDist;
            Plane (*planes)[7];
            EdgeSet (*edgeSets)[7];
            int j;

            if (fn_80201B3C() != NULL) {
                current = fn_80201BC8();
            } else {
                current = NULL;
            }
            player = fn_80050950();
            if (fn_80201ADC() != NULL) {
                target = fn_80201BC8();
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
            planes = table->planes;
            edgeSets = table->edges;
            for (j = 0; j < portal->count; j++) {
                Plane *plane = &planes[portal->index][j];
                EdgeSet *edges = &edgeSets[portal->index][j];
                void *back = plane->unk38;
                float dist;
                int hits;

                hits = fn_8013D998(selfBuf, plane, edges, scratch);
                hits += fn_8013D998(selfBuf, back, edges, scratch);
                selfHits += hits;
                hits = fn_8013D998(otherBuf, plane, edges, scratch);
                hits += fn_8013D998(otherBuf, back, edges, scratch);
                otherHits += hits;
                dist = -(plane->dist + fn_80211B44(&plane->normal, (Vec3 *)selfBuf));
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
                    a = *bestPoint;
                    b = bestEdges->points[0];
                    portal->callback(&b, &a, 0, portal->userData);
                }
            }
        }
    }
    return result;
}
