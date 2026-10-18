typedef struct Vec3 { float x, y, z; } Vec3;

extern float lbl_80650350;
extern float PSVECDotProduct(const Vec3*, const Vec3*);

int fn_8013DF4C(const Vec3* origin, const Vec3* point,
                const Vec3* normal, float distance, Vec3* result)
{
    float denominator = -PSVECDotProduct(origin, normal);
    float amount = distance - denominator;
    if (amount >= lbl_80650350) {
        denominator = PSVECDotProduct(point, normal);
        if (lbl_80650350 != denominator) {
            float scale = amount / -denominator;
            result->x = origin->x + scale * point->x;
            result->y = origin->y + scale * point->y;
            result->z = origin->z + scale * point->z;
            return 1;
        }
    }
    return 0;
}
