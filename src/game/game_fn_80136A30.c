typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef float Mtx[3][4];
typedef struct Quaternion { float x, y, z, w; } Quaternion;
typedef struct QueryResult {
    int kind;
    int flags;
    Vec3 position;
    unsigned char unused[0x14];
} QueryResult;

extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void fn_8011F114(Vec3*, Vec3*);
extern void* fn_8011FE34(void*);
extern void PSMTXQuat(Mtx, const Quaternion*);
extern unsigned int PSMTXInverse(const Mtx, Mtx);
extern void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);
extern void PSMTXMultVec(const Mtx, const Vec3*, Vec3*);
extern void PSVECAdd(const Vec3*, const Vec3*, Vec3*);
extern int fn_80136840(const Vec3*, void*, Result*, float);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern float lbl_806502A0;

int fn_80136A30(const Vec3* point, void* object, Result* out, float radius)
{
    Mtx matrix;
    Mtx inverse;
    QueryResult query;
    Result candidate;
    Vec3 position;
    Vec3 center;
    float best;
    int found;
    int i;
    int count;
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
    PSMTXQuat(matrix, fn_8011FE34(object));
    PSMTXInverse(matrix, inverse);
    PSVECSubtract(point, &position, &center);
    PSMTXMultVec(inverse, &center, &center);

    for (i = 0; i < count; i++, entry = (char*)entry + 0xD8) {
        if (fn_80136840(&center, entry, &candidate, radius)) {
            float distance = PSVECSquareDistance(&center, &candidate.point);
            if (distance < best) {
                best = distance;
                found = 1;
                *out = candidate;
            }
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
