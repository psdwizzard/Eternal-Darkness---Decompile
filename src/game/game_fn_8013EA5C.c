typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    float span_x;
    float pad20;
    float span_z;
} Shape;

extern void fn_8013C264(const Vec3*, const Vec3*, Vec3*, const Vec3*, Vec3*);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);

int fn_8013EA5C(const Shape* shape, const Vec3* point, unsigned short index,
                float extra)
{
    Vec3 closest;
    Vec3 first = shape->first;
    Vec3 second = shape->second;
    Vec3 scratch;
    float radius2 = (extra + shape->radius) * (extra + shape->radius);

    first.z = point->z;
    second.z = point->z;
    fn_8013C264(&first, &second, &scratch, point, &closest);
    if (PSVECSquareDistance(&closest, point) < radius2) {
        float amount;
        amount = (closest.x - shape->first.x) / shape->span_x;
        closest.z = amount * shape->span_z + shape->first.z;
        if (closest.z - shape->radius < point->z + (float)index &&
            closest.z + shape->radius > point->z) {
            return 1;
        }
    }
    return 0;
}
