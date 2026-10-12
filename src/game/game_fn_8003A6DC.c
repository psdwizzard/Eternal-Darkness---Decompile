typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object Object;
typedef struct HitInfo {
    Vec3 start;
    Vec3 end;
    Vec3 position;
    u8 pad[0x0C];
} HitInfo;
typedef struct Candidate {
    int id;
    unsigned int dist;
    unsigned int hit;
    int valid;
} Candidate;
typedef struct QueryResult {
    int header[2];
    Vec3 position;
    Vec3 direction;
    int state[2];
} QueryResult;
typedef struct Flags {
    u8 pad[0xB4];
    unsigned int mask;
} Flags;

extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(void *);
extern int fn_80201B4C(void *);
extern int fn_80201B54(void *);
extern int fn_80201B5C(void *);
extern void *fn_80201B8C(void *);
extern int fn_80201AE4(void);
extern void *fn_80201814(int);
extern void *memset(void *, int, unsigned long);
extern void *fn_801A7778(void *);
extern void fn_8003B0BC(void *, Vec3 *, Vec3 *, void *, void *, int);
extern void fn_8003B630(void *, Vec3 *, Vec3 *, HitInfo *, void *);
extern int fn_8003B2A8(void *, void *, void *, HitInfo *, Candidate *);
extern void fn_800FBE38(void *, int, int, int (*)(const void *, const void *));
extern int fn_8003B878(const void *, const void *);
extern int fn_8011F6A4(void *, int, int, int, QueryResult *, int);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_801A764C(void *, Vec3 *);
extern int fn_801A7498(void *);
extern s16 fn_801A74F8(void *);
extern void fn_801A75A8(void *, int);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern Flags *fn_80036D38(void *);
extern void fn_801A74A8(void *, int);
extern void fn_80072354(int);
extern int fn_80066D04(void *, int);
extern int fn_801E2004(int);
extern void fn_801A7588(void *, u32);
extern void fn_801A7518(void *, s16);
extern u64 fn_8020123C(int, int, int, void *);
extern void fn_8007B3C4(HitInfo *, int, void *, u32);
extern void fn_8002B5B4(HitInfo *, Vec3 *, int, u32);
extern const float lbl_8064E1FC;
extern const float lbl_8064E258;
#define ROUND(x) ((int)((x) >= lbl_8064E1FC ? lbl_8064E258 + (x) : (x) - lbl_8064E258))

extern Vec3 lbl_80238DC4;
extern int lbl_8064CB60;

u32 fn_8003A6DC(void *object, void *target, void *area)
{
    Candidate list[11];
    HitInfo hit;
    QueryResult query;
    Vec3 normal;
    Vec3 position;
    Vec3 pos;
    Vec3 other;
    Vec3 converted;
    Vec3 fallback;
    int style;
    s16 height;
    u32 result;
    int bit;
    void *current;
    int kind;
    void *context;
    void *owner;
    int count;
    int i;
    Vec3 *src;
    Flags *flags;
    u32 mask;
    int n;
    u32 want;
    int id;
    int self;

    result = 0;
    bit = -1;
    current = fn_80201B9C();
    kind = fn_80201EB8(object);
    context = fn_80201BC8(object);
    memset(list, 0, sizeof(list));
    fn_8003B0BC(fn_801A7778(area), &normal, &position, area, context, context != 0);
    fn_8003B630(object, &position, &normal, &hit, 0);
    pos = hit.position;
    count = fn_8003B2A8(object, target, area, &hit, list);
    if (count > 0) {
        if (count > 1) {
            fn_800FBE38(list, count, 0x10, fn_8003B878);
        }
        owner = fn_80201BC8(fn_80201814(list[0].id));
        for (i = 0; i < 16; i++) {
            if (list[0].hit & (1 << i)) {
                bit = i;
                break;
            }
        }
        if (fn_8011F6A4(owner, 0, bit, -1, &query, 1) != -1) {
            hit.end = pos = query.position;
        }
    }
    fn_801A764C(area, &pos);
    style = fn_801A7498(area);
    height = fn_801A74F8(area);
    fn_801A75A8(area, 0x10);
    for (; current != 0; current = fn_80201BC0(current)) {
        void *ref = fn_80201BC8(current);
        if (ref != 0) {
            fn_8011F114(&converted, ref);
            src = &converted;
        } else {
            fallback = lbl_80238DC4;
            src = &fallback;
        }
        other = *src;
        if (kind != fn_80201EB8(current)) {
            continue;
        }
        if (fn_80201B4C(current) != 0 && fn_80201B4C(current) != 1 && fn_80201B5C(current) != 0x39) {
            continue;
        }
        if (fn_80178E94(&pos, &other) >= 500) {
            continue;
        }
        flags = fn_80036D38(current);
        id = fn_80201B54(current);
        fn_801A74A8(area, id);
        mask = 0;
        fn_80072354(*(int *)((u8 *)fn_80201B8C(current) + 0x90));
        n = 0;
        if (bit == 15) {
            mask |= 0x8000;
            n = 1;
        } else {
            self = id == fn_80201AE4();
            for (i = 0; i <= 15; i++) {
                if ((flags != 0 && ((1 << i) & flags->mask) && fn_80066D04(current, i) != 0) ||
                    (self != 0 && fn_801E2004(id) == 4)) {
                    n++;
                    mask |= 1 << i;
                }
            }
        }
        if (bit != -1 && id == list[0].id) {
            want = 1 << bit;
            if (want == mask) {
                fn_801A7588(area, want);
                fn_801A7518(area, height);
                result |= (u32)(fn_8020123C(0xB, style, id, area) & 0xFFFFFFFF);
            } else {
                s16 top;
                fn_801A7588(area, want);
                top = height >> 1;
                fn_801A7518(area, top);
                result |= (u32)(fn_8020123C(0xB, style, id, area) & 0xFFFFFFFF);
                fn_801A7588(area, mask & ~want);
                fn_801A7518(area, ROUND((float)(height - top) / (float)(n - 1)));
                result |= (u32)(fn_8020123C(0xB, style, id, area) & 0xFFFFFFFF);
            }
        } else {
            fn_801A7588(area, mask);
            fn_801A7518(area, ROUND((float)height / (float)n));
            result |= (u32)(fn_8020123C(0xB, style, id, area) & 0xFFFFFFFF);
        }
    }
    fn_8007B3C4(&hit, 1, area, result);
    if (lbl_8064CB60 != 0) {
        fn_8002B5B4(&hit, &hit.position, 0, result);
    }
    return result;
}
