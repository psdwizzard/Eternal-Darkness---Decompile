typedef unsigned char u8;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State {
    u8 pad_00[0x1B4];
    void *handle;
} State;

extern int fn_80128F40(void *);
extern void PSVECSubtract();
extern float PSVECMag(const Vec3 *);
extern void PSVECNormalize(const Vec3 *, Vec3 *);
extern void PSVECScale(const Vec3 *, Vec3 *, float);
extern void fn_80128B8C(void *, Vec3 *);
extern void *fn_80137FB8(void *);
extern float fn_800490E8(float, float);
extern void fn_8012B7A0(void *, float);
extern void fn_80128B34(void *, Vec3 *);
extern const double lbl_8064E888;
extern const float lbl_8064E87C;
extern const float lbl_8064E880;
extern const float lbl_8064E870;

int fn_80074310(void *object, Vec3 *position, State *state, Vec3 *target)
{
    Vec3 direction;
    Vec3 other_direction;
    int height;
    void *other;
    float length;

    height = fn_80128F40(object) >> 17;
    if (height < 36) {
        PSVECSubtract(target, position, &direction);
        length = PSVECMag(&direction);
        PSVECNormalize(&direction, &direction);
        PSVECScale(&direction, &direction, length / ((36 - height) * 2));
        fn_80128B8C(object, &direction);
        other = fn_80137FB8(state->handle);
        if (other != 0) {
            PSVECSubtract(target, other, &other_direction);
            if (PSVECMag(&other_direction) > lbl_8064E87C) {
                fn_8012B7A0(object, lbl_8064E880 + fn_800490E8(other_direction.y, other_direction.x));
            }
        }
        return 1;
    }
    direction.x = lbl_8064E870;
    direction.y = lbl_8064E870;
    direction.z = lbl_8064E870;
    fn_80128B34(object, &direction);
    return 0;
}
