typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern Vec4 *fn_8011FE34(void *object);
extern void fn_8017A244(const Vec3 *axis, Vec4 *rotation, float angle);

void fn_80045918(void *object, const Vec3 *axis, float angle)
{
    Vec3 inverse;

    inverse.x = -axis->x;
    inverse.y = -axis->y;
    inverse.z = -axis->z;
    fn_8017A244(&inverse, fn_8011FE34(object), angle);
}
