typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef float Matrix34[3][4];

typedef struct TraceResult {
    Vec3 start;
    Vec3 end;
    Vec3 displacement;
    u32 distance;
    void *hit;
    unsigned char blocked;
} TraceResult;

typedef struct MergeEntry {
    s32 kind;
    u32 value;
    u32 key;
    s32 count;
} MergeEntry;

extern void *fn_80201BC8(void *);
extern void *memset(void *, int, unsigned long);
extern void fn_801A75A8(void *, int);
extern void *fn_801A7778(void *);
extern void fn_8003B0BC(void *object, Vec3 *normal_out, Vec3 *position_out,
                        void *context, void *transform, int use_transform);
extern u8 fn_80157C00(void *);
extern u32 fn_801578AC(void *);
extern u8 fn_801A76B8(void *);
extern int fn_800FBFB0(void);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_802114E0(Matrix34, void *);
extern void fn_80211710(Matrix34, Vec3 *, Vec3 *);
extern void fn_80211A90(const Vec3 *, Vec3 *, float);
extern void fn_80211A48(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_8003B630(void *object, Vec3 *direction, Vec3 *start,
                        TraceResult *result, void **hit_out);
extern s32 fn_8003B2A8(void *, void *, void *, TraceResult *, MergeEntry *);
extern void fn_800FBE38(void *, int, int, int (*)(const void *, const void *));
extern int fn_8003B878(const void *, const void *);
extern s32 fn_8003B56C(MergeEntry *, s32, MergeEntry *, s32);
extern int fn_801A74F8(void *);
extern void fn_801A7518(void *, int);
extern void *fn_8003B794(void *, MergeEntry *, s32, void *);
extern void fn_8007B3C4(TraceResult *, int, void *, void *);

extern const Vec3 lbl_80238DB8;
extern const float lbl_8064E1FC;

void *fn_8003A280(void *object, void *target, void *anim)
{
    TraceResult traces[10];
    MergeEntry merged[11];
    MergeEntry hits[11];
    Matrix34 matrix;
    Vec3 normal;
    Vec3 position;
    Vec3 up;
    Vec3 dir;
    Vec3 end;
    Vec4 rotation;
    MergeEntry *list;
    void *runtime;
    TraceResult *trace;
    s32 limit;
    s32 i;
    s32 count;
    u32 kind;
    void *source;
    s32 total;
    s32 rays;
    s32 j;
    float ratio;
    u32 layers;
    void *query;

    limit = 0;
    total = 0;
    up = lbl_80238DB8;
    rays = 5;
    runtime = fn_80201BC8(object);
    memset(merged, 0, sizeof(merged));
    memset(hits, 0, sizeof(hits));
    fn_801A75A8(anim, 0x10);
    query = fn_801A7778(anim);
    fn_8003B0BC(query, &normal, &position, anim, runtime, runtime != 0);
    if (query != 0) {
        limit = fn_80157C00(query);
        kind = fn_801578AC(query);
        layers = fn_801A76B8(anim);
        if (kind == 0x40 && layers > 1) {
            rays *= 2;
            up.z *= 2.0f;
        }
    }

    trace = traces;
    for (i = 0; i < rays; i++) {
        fn_8017A244(&position, &rotation, 6.2831855f * (float)(fn_800FBFB0() & 0x1F) / 31.0f);
        fn_802114E0(matrix, &rotation);
        fn_80211710(matrix, &up, &dir);
        fn_80211A90(&dir, &dir, (float)(fn_800FBFB0() & 0x1F) / 31.0f);
        fn_80211A48(&position, &dir, &end);
        fn_8003B630(object, &end, &normal, trace, 0);
        if (i == 0 || total == 0) {
            source = target;
            list = merged;
        } else {
            list = hits;
            source = 0;
            if (i > 1) {
                memset(list, 0, sizeof(hits));
            }
        }
        count = fn_8003B2A8(object, source, anim, trace, list);
        if (count > limit) {
            trace->blocked = 0;
        }
        if (count > 0) {
            if (count > 1) {
                fn_800FBE38(list, count, 0x10, fn_8003B878);
            }
            if (i == 0) {
                total = count;
                if (count > limit + 1) {
                    for (j = limit + 1; j < count; j++) {
                        merged[j].kind = 0;
                        merged[j].value = 0;
                        merged[j].key = 0;
                        merged[j].count = 0;
                    }
                }
            } else {
                total = fn_8003B56C(merged, total, list, count < limit + 1 ? count : limit + 1);
            }
        }
        trace++;
    }

    ratio = (float)(s16)fn_801A74F8(anim) / (float)rays;
    fn_801A7518(anim, (s16)(ratio >= lbl_8064E1FC ? 0.5f + ratio : ratio - 0.5f));
    object = fn_8003B794(object, merged, total, anim);
    fn_8007B3C4(traces, rays, anim, object);
    return object;
}
