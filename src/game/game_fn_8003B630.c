typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Segment {
    Vec3 first;
    Vec3 second;
    Vec3 axis;
    float length;
} Segment;

typedef struct TraceResult {
    Vec3 start;
    Vec3 end;
    Vec3 displacement;
    u32 distance;
    void *hit;
    unsigned char blocked;
} TraceResult;

typedef struct Owner Owner;

extern void *fn_80201BC8(void *);
extern void *fn_8012AB2C(u8 *);
extern void fn_8013F4D0(Segment *, const Vec3 *, const Vec3 *);
extern void *fn_80140258(Owner *, const Vec3 *, Vec3 *, int, void *);
extern void PSVECAdd(const Vec3 *, const Vec3 *, Vec3 *);
extern void PSVECScale(const Vec3 *, Vec3 *, float);
extern float PSVECMag(const Vec3 *);
extern float PSVECDistance(const Vec3 *, const Vec3 *);
extern u32 fn_800F5C54(double);
extern float lbl_8064E264;

void fn_8003B630(void *object, Vec3 *direction, Vec3 *start,
                 TraceResult *result, void **hit_out)
{
    Segment segment;
    Vec3 end;
    Vec3 displacement;
    Vec3 normalized;
    void *runtime;
    Owner *owner;
    void *hit;

    runtime = fn_80201BC8(object);
    if (hit_out != 0) {
        *hit_out = 0;
    }
    result->start = *start;
    PSVECScale(direction, &normalized, lbl_8064E264 / PSVECMag(direction));
    PSVECAdd(start, &normalized, &end);
    owner = fn_8012AB2C(runtime);
    fn_8013F4D0(&segment, start, &end);
    result->blocked = 0;
    hit = fn_80140258(owner, &segment.first, &result->end, 0x15, runtime);
    if (hit != 0) {
        result->blocked = 1;
        if (hit_out != 0) {
            *hit_out = hit;
        }
    } else {
        if (hit_out != 0) {
            *hit_out = 0;
        }
        result->end = end;
    }
    result->hit = hit;
    result->distance = fn_800F5C54(PSVECDistance(start, &result->end));
    PSVECScale(direction, &displacement, (float)result->distance);
    PSVECAdd(start, &displacement, &result->displacement);
}
