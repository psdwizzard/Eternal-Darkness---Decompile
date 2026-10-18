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

extern void PSVECCrossProduct(const Vec3*, const Vec3*, Vec3*);
extern float PSVECMag(const Vec3*);
extern float PSVECDotProduct(const Vec3*, const Vec3*);
extern void PSVECNormalize(const Vec3*, Vec3*);
extern float fn_800490E8(float, float);
extern void fn_8017A244(const Vec3*, Vec4*, float);
extern void fn_8017A630(Vec4*);
extern const double lbl_806508D8;
extern const float lbl_80650860;

void fn_8017A470(const Vec3* first, const Vec3* second,
                 const Vec3* opposite_axis, Vec4* output)
{
    Vec3 axis;
    float length;
    float dot;
    int valid = 1;

    PSVECCrossProduct(first, second, &axis);
    length = PSVECMag(&axis);
    dot = PSVECDotProduct(first, second);

    if (length < lbl_806508D8) {
        if (dot >= lbl_80650860) {
            fn_8017A630(output);
            valid = 0;
        } else if (opposite_axis != 0) {
            axis = *opposite_axis;
        } else {
            fn_8017A630(output);
            valid = 0;
        }
    }

    if (valid != 0) {
        PSVECNormalize(&axis, &axis);
        fn_8017A244(&axis, output, fn_800490E8(length, dot));
    }
}
