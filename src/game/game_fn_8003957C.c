typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct QueryResult {
    u8 pad_0[8];
    Vec3 position;
    Vec3 direction;
    u8 pad_20[8];
} QueryResult;

typedef struct Segment {
    Vec3 start;
    Vec3 end;
} Segment;

typedef struct Actor {
    u8 pad_0[0x9F];
    u8 kind;
} Actor;

extern s32 fn_80039140(void *, void *, void *);
extern s32 fn_80039EF8(s32, void *, void *, s32, Vec3 *, Vec3 *, s32 *);
extern void fn_8003BB04(void *, s32);
extern u32 fn_8004914C(void *);
extern s32 fn_80050950(void);
extern void fn_800C43AC(Vec3 *, void *);
extern s32 fn_8011EB04(void);
extern void fn_8011F114(Vec3 *, void *);
extern s32 fn_8011F6A4(void *, s32, s32, s32, QueryResult *, s32);
extern u8 fn_8012B8A8(void *, Vec3 *);
extern s32 fn_80178E94(Vec3 *, Vec3 *);
extern u16 fn_801A7434(void *);
extern s32 fn_801A7468(void *);
extern void fn_801A7490(void *);
extern void fn_801A74A8(void *, s32);
extern u32 fn_801A74C0(void *);
extern void fn_801A74D8(void *, u32);
extern u32 fn_801A7570(void *);
extern s32 fn_801A7578(void *);
extern Vec3 fn_801A75C0(void *, s32, Vec3 *);
extern void fn_801A7610(void *, Segment);
extern void fn_801A7678(void *, s32);
extern void fn_801A7688(void *, s32, Vec3 *);
extern s32 fn_801A7770(void *);
extern u64 fn_8020123C(s32, s32, s32, s32);
extern void *fn_80201ADC(void);
extern s32 fn_80201B44(void);
extern s32 fn_80201B54(void *);
extern Actor *fn_80201B8C(void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern void fn_80201E78(Vec3 *, void *);
extern s32 fn_80201EB8(void *);
extern s32 fn_80204180(void *, void *);
extern void PSVECSubtract(Vec3 *, Vec3 *, Vec3 *);

s32 fn_8003957C(void *self, void *target, void *area) {
    void *query;
    s32 selfId;
    s32 result;
    s32 checkGroup;
    Actor *actor;
    u32 areaFlags;
    Vec3 selfPos;
    u32 flags;
    s32 sound;
    Vec3 p0;
    Vec3 p1;
    Vec3 p2;
    Vec3 p3;

    if (target != 0) {
        fn_80201B8C(target);
    }
    result = 0;
    checkGroup = 0;
    actor = fn_80201B8C(self);
    areaFlags = fn_801A74C0(area);
    selfId = fn_80201B54(self);
    fn_80201E78(&selfPos, self);
    flags = fn_801A7570(area);
    if (fn_8004914C(area) != 0) {
        sound = fn_8011EB04();
    } else {
        sound = -1;
    }

    query = fn_80201BC8(self);
    if (query != 0) {
        u32 flag80 = flags & 0x80;
        if (flag80 || (flags & 0x100)) {
            s32 idA;
            s32 idB;
            s32 typeA;
            s32 typeB;
            s32 kind = fn_801A7468(area);
            QueryResult hit;
            Segment seg;
            Vec3 dir;

            if (kind == 4 && flag80) {
                idB = 3;
                idA = 3;
                typeA = 3;
                typeB = 2;
            } else if (kind == 5 && flag80) {
                idB = 2;
                idA = 2;
                typeA = 3;
                typeB = 2;
            } else if (kind == 6 && flag80) {
                idA = 3;
                idB = 2;
                typeA = 3;
                typeB = 3;
            } else if (kind == 0x19) {
                idB = -1;
                idA = -1;
                typeA = 3;
                typeB = 2;
            } else if (flags & 0x100) {
                idA = 8;
                idB = 8;
                typeA = 3;
                typeB = 2;
            }
            if (fn_8011F6A4(query, typeA, idA, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 2, &hit.position);
            }
            if (fn_8011F6A4(query, typeB, idB, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 3, &hit.position);
                seg.start = hit.position;
                fn_801A7688(area, 1, &dir);
                PSVECSubtract(&seg.start, &dir, &seg.end);
                fn_801A7610(area, seg);
            }
        } else if (flags & 0x200000) {
            QueryResult hit;
            Segment seg;
            Vec3 dir;

            if (fn_8011F6A4(query, 3, 3, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 2, &hit.position);
            }
            if (fn_8011F6A4(query, 2, 3, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 3, &hit.position);
                seg.start = hit.position;
                fn_801A7688(area, 1, &dir);
                PSVECSubtract(&seg.start, &dir, &seg.end);
                fn_801A7610(area, seg);
            }
        } else if (flags & 0x40) {
            fn_8003BB04(area, 2);
        } else if (flags & 0x2000) {
            s32 id;
            s32 kind = fn_801A7468(area);
            Actor *selfActor = fn_80201B8C(self);
            QueryResult hit;

            if (kind == 4 || kind == 6 || kind == 8) {
                id = 7;
            } else if (kind == 5 || kind == 7 || kind == 9) {
                id = 6;
            } else if (kind == 0x19) {
                id = -1;
            }
            if (fn_8011F6A4(query, 2, id, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 0, &hit.position);
            }
            if (fn_8011F6A4(query, 3, id, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 1, &hit.position);
            }
            if (fn_8011F6A4(query, 0x1C, id, -1, &hit, 1) != -1) {
                if (selfActor->kind == 0x28) {
                    fn_801A75C0(area, 3, &hit.position);
                } else {
                    fn_801A75C0(area, 2, &hit.position);
                }
            }
            if (fn_8011F6A4(query, 0x1D, id, -1, &hit, 1) != -1) {
                if (selfActor->kind == 0x28) {
                    fn_801A75C0(area, 2, &hit.position);
                } else {
                    fn_801A75C0(area, 3, &hit.position);
                }
            }
        }
    }

    fn_801A7688(area, 0, &p0);
    fn_801A7688(area, 1, &p1);
    fn_801A7688(area, 2, &p2);
    fn_801A7688(area, 3, &p3);

    if (target != 0 &&
        (!(areaFlags & 0x20008) || (actor != 0 && actor->kind == 0x28) ||
         (sound == 0xE4 && fn_801A7434(area) == 2))) {
        s32 range = fn_801A7578(area);
        Vec3 targetPos;
        Vec3 pos;

        fn_80201BC8(target);
        fn_800C43AC(&targetPos, target);
        fn_80201E78(&pos, self);
        if (fn_80178E94(&pos, &targetPos) < range &&
            ((flags & 0x8000) || fn_8012B8A8(query, &targetPos))) {
            result = fn_80039140(self, target, area);
            if (result & 3) {
                fn_801A74D8(area, 8);
            } else if (result & 0x40) {
                fn_801A74D8(area, 0x20000);
            }
        }
    }

    areaFlags = fn_801A74C0(area);
    if (selfId == fn_80201B44() && target == 0 && !(areaFlags & 4)) {
        checkGroup = 1;
    }
    if (((areaFlags & 1) || checkGroup) &&
        ((actor != 0 && actor->kind == 0x28) || !(areaFlags & 0x20008))) {
        void *cur = fn_80201B9C();
        s32 saved = fn_801A7770(area);
        s32 range = fn_801A7578(area);

        if (saved != 0xF) {
            fn_801A7678(area, -1);
        }
        for (; cur != 0 && !(areaFlags & 0x20000); cur = fn_80201BC0(cur)) {
            s32 curId = fn_80201B54(cur);
            Vec3 curPos;

            if (cur != target && cur != self) {
                if (fn_80201EB8(cur) == fn_80201EB8(self) &&
                    (u32)(fn_8020123C(0x3B, selfId, curId, 0) & 0xFFFFFFFF) == 1) {
                    void *curQuery = fn_80201BC8(cur);

                    fn_8011F114(&curPos, curQuery);
                    if (fn_80204180(self, cur) < range &&
                        ((flags & 0x8000) || fn_8012B8A8(query, &curPos))) {
                        fn_801A7490(area);
                        fn_801A74A8(area, curId);
                        result |= fn_80039140(self, cur, area);
                        if (result & 3) {
                            fn_801A74D8(area, 8);
                        } else if (result & 0x40) {
                            fn_801A74D8(area, 0x20000);
                        }
                    }
                }
            }
        }
        fn_801A7678(area, saved);
    }

    if (result == 0 && (flags & 0x400) && !(areaFlags & 0x20010)) {
        s32 isPlayer;
        s32 extra = 0;

        isPlayer = fn_80201ADC() == self;

        if (isPlayer) {
            extra = fn_80050950();
        }
        if (fn_80039EF8(isPlayer, area, query, extra, &p0, &p1, &result) == 0 &&
            fn_80039EF8(isPlayer, area, query, extra, &p2, &p3, &result) == 0) {
            fn_80039EF8(isPlayer, area, query, extra, &p1, &p3, &result);
        }
        if (result & 0x40) {
            fn_801A74D8(area, 0x20000);
        }
    }

    if (flags & 0x200) {
        fn_801A7468(area);
        if (flags & 0x40) {
            fn_8003BB04(area, 0);
        } else if (flags & 0x400000) {
            QueryResult hit;

            if (fn_8011F6A4(query, 3, 3, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 0, &hit.position);
            }
            if (fn_8011F6A4(query, 3, 2, -1, &hit, 1) != -1) {
                fn_801A75C0(area, 1, &hit.position);
            }
        } else {
            fn_801A75C0(area, 0, &p3);
            fn_801A75C0(area, 1, &p2);
        }
    }
    return result;
}
