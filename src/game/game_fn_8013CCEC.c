typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ShortVec3 {
    short x, y, z;
} ShortVec3;

extern void PSVECCrossProduct(const Vec3*, const Vec3*, Vec3*);
extern void PSVECNormalize(const Vec3*, Vec3*);
extern void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);
extern float PSVECSquareMag(const Vec3*);
extern float PSVECDotProduct(const Vec3*, const Vec3*);
extern float fn_80027614(float);
extern double fn_80027638(double);
extern int fn_8013CAA8(const Vec3*, int, const ShortVec3*, int, int);
extern float fn_8013CBE4(const Vec3*, const Vec3*, const Vec3*, Vec3*, int);

void fn_8013CCEC(Vec3* output, const Vec3* position,
                 const ShortVec3* vertices, int count, int stride)
{
    Vec3 closest;
    Vec3 previous_point;
    Vec3 next_point;
    Vec3 normal;
    Vec3 first;
    Vec3 second;
    const ShortVec3* current = vertices + stride;
    int axis = 0;
    int nearest;
    int index;
    int previous;
    int next;
    float plane;
    float largest;
    float distance;
    first.x = (float)(vertices[0].x - current->x);
    first.y = (float)(vertices[0].y - current->y);
    first.z = (float)(vertices[0].z - current->z);
    second.x = (float)(vertices[0].x - vertices[stride * 2].x);
    second.y = (float)(vertices[0].y - vertices[stride * 2].y);
    second.z = (float)(vertices[0].z - vertices[stride * 2].z);
    PSVECCrossProduct(&first, &second, &normal);

    first.x = (float)vertices[0].x;
    first.y = (float)vertices[0].y;
    first.z = (float)vertices[0].z;
    PSVECNormalize(&normal, &normal);
    plane = -PSVECDotProduct(&first, &normal);
    largest = fn_80027614(normal.x);
    if (fn_80027638(normal.y) > largest) {
        axis = 1;
    }
    if (fn_80027638(normal.z) > largest) {
        axis = 2;
    }
    distance = -(plane + PSVECDotProduct(position, &normal));
    closest.x = distance * normal.x + position->x;
    closest.y = distance * normal.y + position->y;
    closest.z = distance * normal.z + position->z;
    if (fn_8013CAA8(&closest, count, vertices, axis, stride) != 0) {
        *output = closest;
        return;
    }

    nearest = 0;
    first.x = (float)vertices[0].x;
    first.y = (float)vertices[0].y;
    first.z = (float)vertices[0].z;
    PSVECSubtract(&closest, &first, &second);
    distance = PSVECSquareMag(&second);
    for (index = stride; index < count; index += stride) {
        float candidate;
        first.x = (float)current->x;
        first.y = (float)current->y;
        first.z = (float)current->z;
        PSVECSubtract(&closest, &first, &second);
        candidate = PSVECSquareMag(&second);
        if (candidate < distance) {
            distance = candidate;
            nearest = index;
        }
        current += stride;
    }

    previous = nearest - stride;
    if (previous < 0) {
        previous += count;
    }
    first.x = (float)vertices[nearest].x;
    first.y = (float)vertices[nearest].y;
    first.z = (float)vertices[nearest].z;
    second.x = (float)vertices[previous].x;
    second.y = (float)vertices[previous].y;
    second.z = (float)vertices[previous].z;
    fn_8013CBE4(&first, &second, &closest, &previous_point, 1);

    next = nearest + stride;
    if (next >= count) {
        next -= count;
    }
    second.x = (float)vertices[next].x;
    second.y = (float)vertices[next].y;
    second.z = (float)vertices[next].z;
    fn_8013CBE4(&first, &second, &closest, &next_point, 1);

    PSVECSubtract(&closest, &previous_point, &first);
    PSVECSubtract(&closest, &next_point, &second);
    largest = PSVECSquareMag(&first);
    if (largest < PSVECSquareMag(&second)) {
        *output = previous_point;
    } else {
        *output = next_point;
    }
}
