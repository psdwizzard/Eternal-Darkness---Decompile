typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Segment {
    Vec3 first;
    Vec3 second;
    Vec3 axis;
    float length;
} Segment;

extern float lbl_806503A8, lbl_806503B0;
extern void PSVECSubtract();
extern void PSVECScale(Vec3*, const Vec3*, float);
extern float PSVECMag(const Vec3*);

void fn_8013F4D0(Segment* out, const Vec3* first, const Vec3* second)
{
    out->first = *first;
    out->second = *second;
    PSVECSubtract(second, first, &out->axis);
    out->length = PSVECMag(&out->axis);
    if (lbl_806503A8 != out->length)
        PSVECScale(&out->axis, &out->axis, lbl_806503B0 / out->length);
}
