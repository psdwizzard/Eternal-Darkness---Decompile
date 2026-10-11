typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3Words { unsigned int x, y, z; } Vec3Words;
typedef struct Object Object;
typedef struct HitInfo { u8 bytes[0x30]; } HitInfo;
typedef struct Candidate {
    int id;
    unsigned int dist;
    int hit;
    int valid;
} Candidate;

extern void *fn_80201BC8(void *);
extern int fn_801A7770(void *);
extern void *fn_8004910C(void *);
extern int fn_8011EB04(void *);
extern void fn_801A75A8(void *, int);
extern void *fn_801A7778(void *);
extern void fn_8003B0BC(void *, Vec3 *, Vec3 *, int, int, int);
extern unsigned char fn_80157C00(void *);
extern void fn_8003B630(void *, Vec3 *, Vec3 *, HitInfo *, unsigned short **);
extern int fn_8003B2A8(void *, void *, void *, HitInfo *, Candidate *);
extern void fn_800FBE38(void *, int, int, int (*)(const void *, const void *));
extern int fn_8003B878(const void *, const void *);
extern int fn_8003B794(void *, Candidate *, int, void *);
extern void fn_8007B3C4(Object *, void *, void *, int);
extern void fn_8002B5B4(Vec3Words *, Vec3Words *, int, unsigned int);
extern int lbl_8064CB60;

int fn_8003A0B0(void *object, void *target, void *area)
{
    Vec3 normal;
    Vec3 position;
    HitInfo hit;
    Candidate list[11];
    int result;
    int count;
    int kind;
    void *surface;
    int code;
    register unsigned char previous;
    void *context;
    void *found;

    context = fn_80201BC8(object);
    kind = fn_801A7770(area);
    found = fn_8004910C(area);
    if (found != 0) {
        surface = fn_80201BC8(found);
    } else {
        surface = 0;
    }
    if (found != 0 && surface != 0) {
        code = fn_8011EB04(surface);
        if (kind == 1 && code != 0x61 && code != 0x76 && code != 0x7e &&
            code != 0x71 && code != 0x74 && code != 0x70) {
            fn_801A75A8(area, 0x10);
        }
    }
    surface = fn_801A7778(area);
    fn_8003B0BC(surface, &normal, &position, (int)area, (int)context, context != 0);
    if (surface != 0) {
        previous = (unsigned char)fn_80157C00(surface);
    }
    fn_8003B630(object, &position, &normal, &hit, 0);
    count = fn_8003B2A8(object, target, area, &hit, list);
    if (count > previous) {
        hit.bytes[0x2c] = 0;
    }
    if (count > 0) {
        if (count > 1) {
            fn_800FBE38(list, count, 0x10, fn_8003B878);
        }
        result = count;
        if (count > previous + 1) result = previous + 1;
        count = result;
    }
    result = fn_8003B794(object, list, count, area);
    fn_8007B3C4((Object *)&hit, (void *)1, area, result);
    if (lbl_8064CB60 != 0) {
        fn_8002B5B4((Vec3Words *)&hit, (Vec3Words *)&hit.bytes[0x18], 0, (unsigned int)result);
    }
    return result;
}
