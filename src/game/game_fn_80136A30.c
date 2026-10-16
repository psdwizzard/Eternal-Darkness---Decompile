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
extern void fn_802114E0(Mtx, const Quaternion*);
extern unsigned int fn_802110A8(const Mtx, Mtx);
extern void fn_80211A6C(const Vec3*, const Vec3*, Vec3*);
extern void fn_80211710(const Mtx, const Vec3*, Vec3*);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern int fn_80136840(const Vec3*, void*, Result*, float);
extern float fn_80211D4C(const Vec3*, const Vec3*);
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
    fn_802114E0(matrix, fn_8011FE34(object));
    fn_802110A8(matrix, inverse);
    fn_80211A6C(point, &position, &center);
    fn_80211710(inverse, &center, &center);

    for (i = 0; i < count; i++, entry = (char*)entry + 0xD8) {
        if (fn_80136840(&center, entry, &candidate, radius)) {
            float distance = fn_80211D4C(&center, &candidate.point);
            if (distance < best) {
                best = distance;
                found = 1;
                *out = candidate;
            }
        }
    }
    if (found) {
        fn_80211710(matrix, &out->point, &out->point);
        fn_80211A48(&out->point, &position, &out->point);
        fn_80211710(matrix, &out->normal, &out->normal);
        fn_80211A48(&out->normal, &position, &out->normal);
    }
    return found;
}
