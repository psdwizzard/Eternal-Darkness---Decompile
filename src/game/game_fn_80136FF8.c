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
extern int fn_8013E714(const void* shape, const Vec3* center, Result* out,
                      float radius);
extern int fn_80136C20(const void* shape, void* object, Result* out);
extern float lbl_80650288;

int fn_80136FF8(const void* shape, void* object, Result* out)
{
    Vec3 center;
    Vec3 up;

    if (fn_8011FAEC(object) & 0x100000) {
        float radius = fn_8011F6F0(object);
        up.x = lbl_80650288;
        up.y = lbl_80650288;
        up.z = radius;
        PSVECAdd(fn_8011F130(object), &up, &center);
        return fn_8013E714(shape, &center, out, radius);
    }
    return fn_80136C20(shape, object, out);
}
