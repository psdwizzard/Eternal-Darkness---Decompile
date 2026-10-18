typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Plane {
    Vec3 point;
    Vec3 normal;
} Plane;

extern float lbl_806503B0;
extern void PSVECSubtract();
extern void PSVECScale(Vec3*, const Vec3*, float);
extern float PSVECMag(const Vec3*);
extern float PSVECDotProduct(const Vec3*, const Vec3*);

void fn_8013F600(Plane* out, Vec3* normal, float* distance)
{
    PSVECSubtract(&out->normal, &out->point, normal);
    PSVECScale(normal, normal, lbl_806503B0 / PSVECMag(normal));
    *distance = -PSVECDotProduct(&out->point, normal);
}
