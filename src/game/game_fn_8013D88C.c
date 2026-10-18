typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct FaceRef { unsigned short index; unsigned short pad; const void* data; } FaceRef;

extern float PSVECDotProduct(const Vec3*, const Vec3*);
extern unsigned char fn_8013D260(const Vec3*, const void*, unsigned short, const void*);
extern float lbl_80650350;

int fn_8013D88C(const Vec3* origin, const Vec3* delta, const FaceRef* face,
                float limit, float offset, const Vec3* normal,
                const void* context, Vec3* result)
{
    const void* data;
    unsigned short index;
    float denominator = PSVECDotProduct(normal, delta);
    if (denominator < lbl_80650350) {
        float numerator = -PSVECDotProduct(origin, normal);
        float amount = (offset - numerator) / -denominator;
        if (amount < limit && amount > lbl_80650350) {
            result->x = origin->x + amount * delta->x;
            result->y = origin->y + amount * delta->y;
            result->z = origin->z + amount * delta->z;
            data = ((const volatile FaceRef*)face)->data;
            index = ((const volatile FaceRef*)face)->index;
            return fn_8013D260(result, data, index, context);
        }
    }
    return 0;
}
