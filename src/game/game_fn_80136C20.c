typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Shape {
    Vec3 first, second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;
typedef struct QueryResult {
    int kind, flags;
    Vec3 position;
    unsigned char unused[0x14];
} QueryResult;
typedef float Matrix34[3][4];
typedef struct Quaternion { float x, y, z, w; } Quaternion;

extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void fn_8011F114(Vec3*, Vec3*);
extern void* fn_8011FE34(void*);
extern void PSMTXQuat(Matrix34, const Quaternion*);
extern unsigned int PSMTXInverse(const Matrix34, Matrix34);
extern void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);
extern void PSMTXMultVec(const Matrix34, const Vec3*, Vec3*);
extern void PSVECAdd(const Vec3*, const Vec3*, Vec3*);
extern int fn_80136944(const Vec3*, void*, Result*);
extern void fn_8013F3C0(Shape*, const Vec3*, const Vec3*, float);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern float lbl_806502A0;

int fn_80136C20(const Shape* shape, void* object, Result* out)
{
    Matrix34 matrix;
    Matrix34 inverse;
    QueryResult query;
    Shape localShape;
    Result candidate;
    Vec3 position;
    float best;
    int count;
    int found;
    int i;
    void* collection = *(void**)((char*)object + 0x3C);
    void* entry;
    best = lbl_806502A0;
    count = *(int*)((char*)collection + 0xF0);
    entry = *(void**)((char*)collection + 0xF4);
    found = 0;
    if (fn_8011F6A4(object, 0x1B,
                    (*(int*)((char*)object + 0x244) == 0xFC &&
                     *(int*)((char*)object + 0x248) == 3) ? 1 : 0xF,
                    -1, &query, 1) == -1) {
        fn_8011F114(&position, (Vec3*)object);
    } else {
        position = query.position;
    }
    PSMTXQuat(matrix, (const Quaternion*)fn_8011FE34(object));
    PSMTXInverse(matrix, inverse);
    PSVECSubtract(&shape->first, &position, &localShape.first);
    PSMTXMultVec(inverse, &localShape.first, &localShape.first);
    PSVECSubtract(&shape->second, &position, &localShape.second);
    PSMTXMultVec(inverse, &localShape.second, &localShape.second);
    fn_8013F3C0(&localShape, &localShape.first, &localShape.second,
                shape->radius);

    for (i = 0; i < count; i++, entry = (char*)entry + 0xD8) {
        if (fn_80136944(&localShape.first, entry, &candidate)) {
            float distance = PSVECSquareDistance(&localShape.first, &candidate.point);
            if (distance < best) {
                best = distance;
                *out = candidate;
            }
            found = 1;
        }
    }
    if (found) {
        PSMTXMultVec(matrix, &out->point, &out->point);
        PSVECAdd(&out->point, &position, &out->point);
        PSMTXMultVec(matrix, &out->normal, &out->normal);
        PSVECAdd(&out->normal, &position, &out->normal);
    }
    return found;
}
