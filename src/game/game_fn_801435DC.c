typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Segment {
    Vec3 start;
    Vec3 end;
    Vec3 direction;
    float distance;
} Segment;

extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern unsigned int fn_80178E94(const float *first, const float *second);
extern void PSVECAdd(const Vec3 *first, const Vec3 *second, Vec3 *result);
extern void PSVECSubtract(const Vec3 *first, const Vec3 *second, Vec3 *result);
extern void PSVECScale(const Vec3 *source, Vec3 *result, float scale);
extern void PSVECNormalize(const Vec3 *source, Vec3 *result);
extern float lbl_80650448;
extern float lbl_80650450;

void fn_801435DC(Vec3 *first, Vec3 *second, Segment *out)
{
    Vec3 secondPosition;
    Vec3 direction;
    Vec3 firstPosition;
    float height;

    fn_8011F114(&firstPosition, first);
    out->start = firstPosition;
    fn_8011F114(&secondPosition, second);
    PSVECSubtract(&secondPosition, &out->start, &direction);
    PSVECNormalize(&direction, &direction);
    PSVECScale(&direction, &direction, lbl_80650450);
    PSVECAdd(&out->start, &direction, &out->end);
    out->start.z += (height = lbl_80650448);
    out->end.z += height;
    PSVECSubtract(&out->end, &out->start, &out->direction);
    PSVECNormalize(&out->direction, &out->direction);
    out->distance = (float)fn_80178E94(&out->start.x, &out->end.x);
}
