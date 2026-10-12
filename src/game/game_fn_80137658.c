typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

extern unsigned int fn_8011FAEC(void* object);
extern unsigned short fn_8011F760(void* object);
extern float fn_8011F6F0(void* object);
extern Vec3* fn_8011F130(void* object);
extern void fn_80211A48(const Vec3* a, const Vec3* b, Vec3* out);
extern void fn_80211A6C(const Vec3* a, const Vec3* b, Vec3* out);
extern int fn_80136F04(const Vec3* point, void* object, Result* out,
                      float radius, float height);
extern int fn_80136E30(const Vec3* point, void* object, Result* out,
                      float radius);
extern int fn_80136A30(const Vec3* point, void* object, Result* out,
                      float radius);
extern float lbl_80650288;

int fn_80137658(void* self, const Vec3* point, void* object, Result* out,
                float radius)
{
    Vec3 bottom;
    Vec3 offset;
    Vec3 up;
    Vec3 center;

    if (fn_8011FAEC(self) & 0x100000) {
        if (fn_8011FAEC(object) & 0x100000) {
            offset.z = radius;
            offset.x = lbl_80650288;
            offset.y = lbl_80650288;
            fn_80211A6C(point, &offset, &bottom);
            return fn_80136F04(&bottom, object, out, radius,
                               fn_8011F760(self));
        }
        return fn_80136E30(point, object, out, radius);
    }
    if (fn_8011FAEC(object) & 0x100000) {
        float objectRadius = fn_8011F6F0(object);
        up.x = lbl_80650288;
        up.y = lbl_80650288;
        up.z = objectRadius;
        fn_80211A48(fn_8011F130(object), &up, &center);
        return fn_80136A30(&center, self, out, objectRadius);
    }
    return 0;
}
