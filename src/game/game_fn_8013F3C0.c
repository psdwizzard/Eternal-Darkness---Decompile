typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

extern const float lbl_806503A8, lbl_806503AC, lbl_806503B0, lbl_806503B4;
extern void fn_80211A6C();
extern void fn_80211A90(Vec3*, const Vec3*, float);
extern float fn_80211B08(const Vec3*);

void fn_8013F3C0(Shape* out, const Vec3* first, const Vec3* second, float radius)
{
    float half;
    out->first = *first;
    out->second = *second;
    out->radius = radius;
    if (lbl_806503A8 == out->radius)
        out->radius = lbl_806503AC;
    fn_80211A6C(second, first, &out->axis);
    out->length = fn_80211B08(&out->axis);
    if (lbl_806503A8 != out->length)
        fn_80211A90(&out->axis, &out->axis, lbl_806503B0 / out->length);
    half = lbl_806503B4;
    out->bound_radius = half * out->length + radius;
    out->center.x = half * (out->first.x + out->second.x);
    out->center.y = half * (out->first.y + out->second.y);
    out->center.z = half * (out->first.z + out->second.z);
}
