typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

extern unsigned int fn_8011FAEC(void* object);
extern float fn_8011F6F0(void* object);
extern Vec3* fn_8011F130(void* object);
extern void PSVECAdd(const Vec3* a, const Vec3* b, Vec3* out);
extern int fn_8013EF30(const Vec3* center, const Vec3* point, Result* out,
                      float radius, float extra);
extern void fn_80136A30(const Vec3* point, void* object, Result* out,
                       float extra);
extern float lbl_80650288;

void fn_80136E30(const Vec3* point, void* object, Result* out, float extra)
{
    Vec3 center;
    Vec3 up;

    if (fn_8011FAEC(object) & 0x100000) {
        float radius = fn_8011F6F0(object);
        up.x = lbl_80650288;
        up.y = lbl_80650288;
        up.z = radius;
        PSVECAdd(fn_8011F130(object), &up, &center);
        fn_8013EF30(&center, point, out, radius, extra);
    } else {
        fn_80136A30(point, object, out, extra);
    }
}
