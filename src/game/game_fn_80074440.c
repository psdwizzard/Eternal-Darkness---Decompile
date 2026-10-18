typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef float Matrix[3][4];

typedef struct MatrixWorkspace {
    Vec3 reserved;
    Matrix value;
} MatrixWorkspace;

extern int fn_80074580(void *, void *, Vec3 *, Vec3 *, Vec3 *);
extern float fn_8011F6F0(void *);
extern void *fn_8012AB2C(void *);
extern void fn_8013F3C0(Matrix, const Vec3 *, const Vec3 *, float);
extern int fn_8013FDB4(void *, Matrix, Vec3 *, void *, int, void *);
extern float PSVECDistance(const Vec3 *, Vec3 *);
extern const float lbl_8064E890;

int fn_80074440(void *object, void *other, Vec3 *position, Vec3 *target)
{
    int detail;
    Vec3 hit;
    Vec3 normal;
    Vec3 first;
    Vec3 second;
    Vec3 candidate;
    MatrixWorkspace matrix;
    float height;
    void *world;
    int result;

    result = fn_80074580(object, other, &candidate, position, target);
    if (result != 0) {
        height = fn_8011F6F0(object);
        world = fn_8012AB2C(object);
        first = candidate;
        first.z += height;
        second = *target;
        second.z += height;
        fn_8013F3C0(matrix.value, &first, &second, height);
        if (fn_8013FDB4(world, (float (*)[4])(&matrix.reserved + 1), &hit,
                        object, 11, &detail) != 0) {
            normal = hit;
            if (PSVECDistance(target, &normal) > lbl_8064E890) {
                result = 0;
            }
        }
    }
    return result;
}
