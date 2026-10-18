typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Ray { Vec3 origin; unsigned char pad[12]; Vec3 direction; float limit; } Ray;
typedef struct Plane { unsigned char pad[20]; Vec3 normal; float offset; } Plane;

extern float PSVECDotProduct(const Vec3*, const Vec3*);
extern int fn_8013D560(const Vec3*, const Plane*, const void*);
extern float lbl_80650350;

int fn_8013D998(const Ray* ray, const Plane* plane, const void* context,
                Vec3* result)
{
    float dot = -PSVECDotProduct(&ray->origin, &plane->normal);
    float distance = plane->offset - dot;
    if (distance >= lbl_80650350) {
        float denominator = PSVECDotProduct(&ray->direction, &plane->normal);
        if (lbl_80650350 != denominator) {
            float amount = distance / -denominator;
            if (amount <= ray->limit && amount >= lbl_80650350) {
                result->x = ray->origin.x + amount * ray->direction.x;
                result->y = ray->origin.y + amount * ray->direction.y;
                result->z = ray->origin.z + amount * ray->direction.z;
                if (fn_8013D560(result, plane, context)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
