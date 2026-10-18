typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Transform {
    float pad[4];
    float scale;
} Transform;

extern float lbl_8064F1FC;

extern void *fn_80201BC8();
extern float fn_8011F6F0(void);
extern void fn_8011F114();
extern void PSVECSubtract();
extern void PSVECNormalize(Vec3 *, const Vec3 *);
extern void PSVECScale(Vec3 *, Vec3 *, float);
extern void PSVECAdd(Vec3 *, const Vec3 *, Vec3 *);
extern void fn_8012AC74(void *, Vec3 *, int);

void fn_800C677C(void *object, Transform *transform, int mode)
{
    Vec3 result;
    Vec3 direction;
    Vec3 scaled_transform;
    Vec3 scaled_time;
    Vec3 origin;
    void *node;
    float time;

    node = fn_80201BC8(object);
    time = fn_8011F6F0() / lbl_8064F1FC;
    fn_8011F114(&origin, node);
    PSVECSubtract(transform, &origin, &direction);
    PSVECNormalize(&direction, &direction);
    PSVECScale(&direction, &scaled_transform, transform->scale);
    PSVECScale(&direction, &scaled_time, time);

    switch (mode) {
    case 0:
        PSVECAdd(&origin, &scaled_transform, &result);
        PSVECAdd(&result, &scaled_time, &result);
        break;
    case 1:
        PSVECSubtract(&origin, &scaled_transform, &result);
        PSVECSubtract(&result, &scaled_time, &result);
        break;
    }
    fn_8012AC74(node, &result, 3);
}
