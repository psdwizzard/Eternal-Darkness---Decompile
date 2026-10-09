typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct PathNode {
    unsigned char pad00[0x2C];
    short x;
    short y;
    short z;
    unsigned char pad32[0x48 - 0x32];
    unsigned int flags;
} PathNode;

typedef struct PathSet {
    unsigned char pad00[0x34];
    unsigned short count;
    unsigned char pad36[2];
    PathNode *nodes;
} PathSet;

typedef struct ObjData {
    unsigned char pad00[0x9F];
    unsigned char kind;
} ObjData;

extern void *lbl_8064C4E4;
extern int lbl_8064D18C;
extern float lbl_8064F2B4;

extern void *fn_80201B3C(void);
extern void *fn_80201BC8(void *);
extern void fn_80201E78(Vec3 *, void *);
extern int fn_80201B54(void *);
extern ObjData *fn_80201B8C(void *);
extern unsigned int fn_80178E94(Vec3 *, Vec3 *);
extern float fn_8011F6F0(void *);
extern unsigned int fn_800F5C54(double);
extern void **fn_800BC100(int, Vec3 *, int *, int, int, int, int);
extern void fn_800BCCC4(void *, Vec3 *);
extern void fn_8011F0E8(void *, Vec3 *);
extern PathSet *fn_8015C390(int);
extern unsigned int fn_80178F14(int, int, int, int, int, int);
extern int fn_800CB254(int, int, Vec3 *, int, int);
extern void fn_80048708(void *);

int fn_800C9E50(void *obj)
{
    Vec3 targetPos;
    Vec3 objPos;
    Vec3 spot;
    Vec3 pos;
    int type;
    void *target;
    void *actor;
    unsigned int dist;
    ObjData *data;
    unsigned int range;
    int found;
    PathSet *set;
    PathNode *best;
    unsigned int bestDist;
    PathNode *node;
    unsigned int nodeDist;
    int i;
    void **hit;

    target = fn_80201B3C();
    found = 0;
    actor = fn_80201BC8(obj);
    fn_80201E78(&objPos, obj);
    fn_80201E78(&targetPos, target);
    fn_80201B54(obj);
    dist = fn_80178E94(&objPos, &targetPos);
    data = fn_80201B8C(obj);
    range = fn_800F5C54(lbl_8064F2B4 + (fn_8011F6F0(actor) + fn_8011F6F0(lbl_8064C4E4)));

    if (lbl_8064D18C == 0xC2 && data != 0 && data->kind == 4) {
        type = 0xD;
        hit = fn_800BC100(0, &targetPos, &type, 0x10, 0, 0, 0);
        if (hit != 0 && *hit != 0) {
            fn_800BCCC4(*hit, &spot);
            fn_8011F0E8(actor, &spot);
        }
    }

    if (dist < range) {
        best = 0;
        set = fn_8015C390(2);
        bestDist = -1;
        if (set != 0 && set->count != 0) {
            node = set->nodes;
            for (i = 0; i < set->count; i++, node++) {
                if (node->flags & 0x40) {
                    pos.x = node->x;
                    pos.y = node->y;
                    pos.z = node->z;
                    nodeDist = fn_80178F14((int)pos.x, (int)pos.y, (int)pos.z,
                                           (int)targetPos.x, (int)targetPos.y, (int)targetPos.z);
                    if (nodeDist < bestDist && fn_800CB254(0, 0x5A, &pos, lbl_8064D18C, 0) == 0) {
                        bestDist = nodeDist;
                        best = node;
                    }
                }
            }
            if (best != 0) {
                found = 1;
                pos.x = best->x;
                pos.y = best->y;
                pos.z = best->z;
                fn_8011F0E8(actor, &pos);
            } else {
                fn_80048708(actor);
            }
        }
    }
    return found;
}
