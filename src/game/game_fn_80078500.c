typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern int fn_80128EAC(void *object);
extern void fn_8011F114();
extern int fn_80128F40(void *object);
extern int fn_8012A1BC(void *object, int kind);
extern void *fn_80201B8C();
extern Vec3 *fn_80137FB8(void *handle);
extern void PSVECSubtract();
extern float PSVECMag(const Vec3 *value);
extern void PSVECNormalize(const Vec3 *input, Vec3 *output);
extern void PSVECScale(const Vec3 *input, Vec3 *output, float scale);
extern void fn_80128B8C(void *object, Vec3 *value);
/* NonMatching: behavior-complete direction interpolation. Instructions match;
 * the split TU names its compiler-generated int-to-double constant locally. */
int fn_80078500(void *object, void *context)
{
    Vec3 direction;
    Vec3 position;

    if (fn_80128EAC(object) == 0x4C) {
        int packed;
        int maximum;
        float length;
        void *state;
        Vec3 *target;

        fn_8011F114(&position, object);
        packed = fn_80128F40(object);
        maximum = fn_8012A1BC(object, 0x4C);
        state = *(void **)((u8 *)fn_80201B8C(context) + 0x44);
        target = fn_80137FB8(*(void **)((u8 *)state + 0x1B4));
        PSVECSubtract(target, &position, &direction);
        length = PSVECMag(&direction);
        PSVECNormalize(&direction, &direction);
        PSVECScale(&direction, &direction,
                    length / ((maximum - (packed >> 17)) * 2));
        fn_80128B8C(object, &direction);
    }
    return 1;
}
