typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Matrix34 { float m[3][4]; } Matrix34;

extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void fn_8011F114(Vec3*, void*);
extern void* fn_8011FE34(void*);
extern void fn_802114E0(Matrix34*, void*);
extern void fn_802110A8(Matrix34*, Matrix34*);
extern void fn_80211A6C(void*, const Vec3*, Vec3*);
extern void fn_80211710(Matrix34*, const Vec3*, Vec3*);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern int fn_80136944(const Vec3*, void*, Result*);
extern void fn_8013F3C0(void*, const Vec3*, const Vec3*, float);
extern float fn_80211D4C(const Vec3*, const Vec3*);
extern float lbl_806502A0;

int fn_80136C20(void* shape, void* object, Result* out)
{
    Result candidate;
    Vec3 position;
    Vec3 center;
    Vec3 transformed;
    Matrix34 matrix;
    Matrix34 inverse;
    struct { int pad[2]; unsigned int value[3]; } query;
    float best;
    int count;
    int i;
    int found = 0;
    void* collection = *(void**)((char*)object + 0x3C);
    void* entry = *(void**)((char*)collection + 0xF4);
    count = *(int*)((char*)collection + 0xF0);

    best = lbl_806502A0;
    if (fn_8011F6A4(object, 0x1B,
                    (*(int*)((char*)object + 0x244) == 0xFC &&
                     *(int*)((char*)object + 0x248) == 3) ? 1 : 0xF,
                    -1, &query, 1) == -1) {
        fn_8011F114(&position, object);
    } else {
        *(unsigned int*)&position.x = query.value[0];
        *(unsigned int*)&position.y = query.value[1];
        *(unsigned int*)&position.z = query.value[2];
    }
    fn_802114E0(&matrix, fn_8011FE34(object));
    fn_802110A8(&matrix, &inverse);
    fn_80211A6C(shape, &position, &center);
    fn_80211710(&inverse, &center, &center);
    fn_80211A6C((char*)shape + 0xC, &position, &transformed);
    fn_80211710(&inverse, &transformed, &transformed);
    fn_8013F3C0(&center, &center, &transformed,
                *(float*)((char*)shape + 0x18));

    for (i = 0; i < count; i++, entry = (char*)entry + 0xD8) {
        if (fn_80136944(&center, entry, &candidate)) {
            float distance = fn_80211D4C(&center, &candidate.point);
            if (distance < best) {
                best = distance;
                *out = candidate;
            }
            found = 1;
        }
    }
    if (found) {
        fn_80211710(&matrix, &out->point, &out->point);
        fn_80211A48(&out->point, &position, &out->point);
        fn_80211710(&matrix, &out->normal, &out->normal);
        fn_80211A48(&out->normal, &position, &out->normal);
    }
    return found;
}
