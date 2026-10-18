typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const float lbl_80651464;
extern const float lbl_806514B0;
extern const float lbl_806514D4;

extern void fn_801F68B0(Vec3*);
extern void fn_801F68D4(Vec3*);
extern float fn_801F691C(void);
extern float fn_8003315C(float);
extern void PSVECSubtract(Vec3*, Vec3*, Vec3*);
extern void PSVECNormalize(Vec3*, Vec3*);
extern float PSVECDotProduct(Vec3*, Vec3*);

int fn_801FBC18(Vec3* vector, float threshold)
{
    Vec3 first_copy;
    Vec3 second_copy;
    Vec3 first;
    Vec3 second;
    float dot;
    float random;
    int result = 0;

    fn_801F68D4(&first);
    first_copy = first;
    fn_801F68B0(&second);
    second_copy = second;
    PSVECSubtract(vector, &second_copy, vector);
    PSVECNormalize(vector, vector);
    dot = PSVECDotProduct(vector, &first_copy);
    if (dot > lbl_80651464) {
        random = fn_801F691C();
        dot = lbl_806514D4 * fn_8003315C(dot);
        random *= lbl_806514B0;
        random -= dot;
        if (random > threshold) {
            result = 1;
        }
    }
    return result;
}
