typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Segment {
    Vec3 first, second, axis;
    float length;
} Segment;
typedef struct HitTriangle { Vec3 a, b, c; } HitTriangle;
typedef struct Query {
    Vec3 start;
    Vec3 direction;
    Vec3 end;
    u32 max_distance;
} Query;
typedef struct Candidate {
    int id;
    u32 distance;
    int mask;
    int valid;
} Candidate;

extern int fn_80036B7C(void*, int, Vec3*);
extern void fn_8011F114(Vec3*, Vec3*);
extern float fn_80123708(void*, int);
extern unsigned char fn_8012B8A8(void*, Vec3*);
extern int fn_8013638C(Vec3*, Vec3*, void*, HitTriangle*, float*, float);
extern void fn_8013F4D0(Segment*, const Vec3*, const Vec3*);
extern void* fn_8014317C(Segment*, Vec3*, void*, Vec3*, u32);
extern u32 fn_80178E94(const void*, const void*);
extern int fn_801A7498(void*);
extern u32 fn_801A74C0(void*);
extern int fn_801A7770(void*);
extern u64 fn_8020123C(int, int, int, int);
extern int fn_80201B4C(void*);
extern int fn_80201B54(void*);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern void* fn_80201BC8(void*);
extern int fn_80201EB8(void*);
extern u32 fn_80204180(void*, void*);
extern float lbl_8064E260;

static inline Vec3* candidate_position(void* object, Vec3* position)
{
    Vec3* data = fn_80201BC8(object);
    fn_8011F114(position, data);
    return data;
}

int fn_8003B2A8(register void* object, register void* target, register void* area,
                register Query* query, register Candidate* results)
{
    Segment segment;
    HitTriangle triangle;
    Vec3 position;
    Vec3 first;
    Vec3 second;
    Vec3 intersection;
    float distance;
    register Vec3* data;
    register void* source;
    register int area_id;
    register void* current;
    register int count;
    register Candidate* entry;
    register u32 flags;
    register u32 options;
    register u32 ignore_distance;
    register void* target_data;
    register int bit;
    register u32 target_distance;
    register int id;
    register int mask;

    current = fn_80201B9C();
    count = 0;
    flags = fn_801A74C0(area);
    area_id = fn_801A7498(area);
    source = fn_80201BC8(object);
    options = fn_801A74C0(area);
    if (target != 0 && (fn_801A74C0(area) & 0x01000000)) {
        target_data = fn_80201BC8(target);
        bit = fn_801A7770(area);
        fn_80036B7C(target_data, bit, &position);
        target_distance = fn_80178E94(query, &position);
        if (target_distance < query->max_distance || (options & 0x2000)) {
            fn_8011F114(&first, source);
            fn_8011F114(&second, target_data);
            second.z += lbl_8064E260;
            first.z = second.z;
            fn_8013F4D0(&segment, &first, &second);
            if (fn_8014317C(&segment, &intersection, source, &second, 1) == 0) {
                results->id = fn_80201B54(target);
                count = 1;
                results->distance = target_distance;
                results->mask = 1 << bit;
                results->valid = 1;
            }
        }
    }
    if (flags & 1) {
        entry = results + count;
        ignore_distance = options & 0x2000;
        while (current != 0 && count < 11) {
            id = fn_80201B54(current);
            if (fn_80201EB8(current) == fn_80201EB8(object) && fn_80201B4C(current) == 1 &&
                current != object && (current != target || !(fn_801A74C0(area) & 0x01000000)) &&
                (u32)(fn_8020123C(0x3B, area_id, id, 0) & 0xFFFFFFFFULL) == 1) {
                data = candidate_position(current, &position);
                if ((fn_80204180(object, current) < query->max_distance || ignore_distance) &&
                    fn_8012B8A8(source, &position)) {
                    mask = fn_8013638C(&query->start, &query->end, data, &triangle, &distance,
                                          fn_80123708(data, 0));
                    if (mask != 0) {
                        entry->id = id;
                        entry->distance = fn_80178E94(query, &position);
                        count++;
                        entry->mask = mask;
                        entry->valid = 1;
                        entry++;
                    }
                }
            }
            current = fn_80201BC0(current);
        }
    }
    return count;
}
