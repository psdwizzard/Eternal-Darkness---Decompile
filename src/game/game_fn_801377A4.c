typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct Capsule {
    Vec3 start;
    Vec3 end;
    float radius;
    Vec3 axis;
    float length;
    Vec3 extra;
    float extraScale;
} Capsule;

typedef struct Cylinder {
    unsigned char data[0x34];
} Cylinder;

extern unsigned int fn_8011FAEC(void* object);
extern Vec3* fn_8011F130(void* object);
extern unsigned short fn_8011F760(void* object);
extern void fn_80211A48(const Vec3* a, const Vec3* b, Vec3* out);
extern void fn_80211A6C(const Vec3* a, const Vec3* b, Vec3* out);
extern void fn_80211A90(const Vec3* in, Vec3* out, float scale);
extern void fn_8013F564(Cylinder* out, const Vec3* bottom, const Vec3* top,
                        float radius, float height);
extern int fn_80136C20(const void* shape, void* object, Result* out);
extern int fn_80136F04(const Capsule* capsule, void* object, Result* out,
                       float radius, float height);
extern int fn_80136FF8(const void* shape, void* object, Result* out);
extern int fn_801370B0(const Cylinder* cylinder, void* object, Result* out);
extern float lbl_80650288;
extern float lbl_806502A4;
extern float lbl_806502A8;
extern float lbl_806502AC;

int fn_801377A4(void* self, const Capsule* capsule, void* object, Result* out)
{
    Cylinder cylinder;
    Capsule local;
    Result result;
    Vec3 bottom;
    Vec3 top;
    Vec3 up;
    Vec3 offset;
    int hit;

    if (fn_8011FAEC(self) & 0x100000) {
        if (fn_8011FAEC(object) & 0x100000) {
            up.x = lbl_80650288;
            up.y = lbl_80650288;
            up.z = capsule->radius;
            fn_80211A6C(&capsule->start, &up, &bottom);
            fn_80211A6C(&capsule->end, &up, &top);
            fn_8013F564(&cylinder, &bottom, &top, capsule->radius,
                        fn_8011F760(self));
            if (capsule->length >= lbl_806502A4 &&
                capsule->length <= lbl_806502A8) {
                return fn_80136F04(capsule, object, out, capsule->radius,
                                   fn_8011F760(self));
            }
            return fn_801370B0(&cylinder, object, out);
        }
        return fn_80136FF8(capsule, object, out);
    }
    if (fn_8011FAEC(object) & 0x100000) {
        local.start = *fn_8011F130(object);
        fn_80211A90(&capsule->axis, &offset, -capsule->length);
        fn_80211A48(&local.start, &offset, &local.end);
        local.length = capsule->length;
        local.radius = capsule->radius;
        fn_80211A90(&capsule->axis, &local.axis, lbl_806502AC);
        local.extra = capsule->extra;
        local.extraScale = capsule->extraScale;
        hit = fn_80136C20(&local, self, &result);
        if (hit) {
            out->normal = result.point;
            out->point = result.normal;
        }
        return hit;
    }
    return 0;
}
