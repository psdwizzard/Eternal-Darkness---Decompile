typedef signed int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern unsigned int rand(void);
#define rand() ((int)rand())
extern void PSVECNormalize(Vec3 *out, const Vec3 *in);
extern void PSVECScale(Vec3 *out, const Vec3 *in, float scale);
extern void fn_80205868(void *object, s32 kind, const Vec3 *direction, s32 flags);

extern const float lbl_8064E700;
extern const float lbl_8064E704;
extern const double lbl_8064E708;

void fn_800685A4(void *object, s32 kind)
{
    Vec3 direction;

    direction.x = (float)(2 - (rand() & 3));
    direction.y = (float)(2 - (rand() & 3));
    direction.z = lbl_8064E700;
    PSVECNormalize(&direction, &direction);
    PSVECScale(&direction, &direction, lbl_8064E704);
    fn_80205868(object, kind, &direction, 0x2000);
}
