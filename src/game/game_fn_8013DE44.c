typedef struct Vec3 { float x, y, z; } Vec3;

extern float lbl_80650350;
extern float lbl_8065035C;
extern float lbl_80650360;
extern float lbl_80650364;
extern void PSVECSubtract();
extern float PSVECDotProduct(const Vec3*, const Vec3*);
extern float fn_800ED720(float);

int fn_8013DE44(const Vec3* a, const Vec3* b, const Vec3* c,
                float radius, float* result, unsigned char alternate)
{
    Vec3 delta;
    float projection;
    float discriminant;

    PSVECSubtract(a, c, &delta);
    projection = PSVECDotProduct(b, &delta);
    projection = lbl_8065035C * projection;
    discriminant = projection * projection -
        lbl_80650360 * (PSVECDotProduct(&delta, &delta) - radius * radius);
    if (discriminant >= lbl_80650350) {
        float distance;

        distance = -projection - fn_800ED720(discriminant);
        *result = distance * lbl_80650364;
        if (!alternate && *result < lbl_80650350) {
            distance = -projection + fn_800ED720(discriminant);
            *result = distance * lbl_80650364;
        }
        return 1;
    }
    return 0;
}
