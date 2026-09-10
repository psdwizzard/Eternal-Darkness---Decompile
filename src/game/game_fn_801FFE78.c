typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void fn_80179C10(Vec3*, float, float, const Vec3*, float, u8);
extern int fn_80179EB8(const Vec3*);
extern void fn_801ECD74(const void*);
extern void fn_801ECF50(int);
extern void fn_801ED118(void);
extern void fn_801ED468(int);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_80200320(void);
extern void fn_80200324(float, float, float);
extern void fn_80211A48(Vec3*, const Vec3*, const Vec3*);
extern void fn_80211A6C(const Vec3*, const Vec3*, Vec3*);
extern void fn_80211AAC(const Vec3*, Vec3*);
extern float fn_80211B44(const Vec3*, const Vec3*);
extern void fn_80226AB4(int, int, int);
extern void fn_80226D28(int);

void fn_801FFE78(Vec3* first_center, Vec3* axis, Vec3* second_center,
                 u8 sides, u32* color, u8 alpha,
                 float first_x, float first_y,
                 float second_x, float second_y)
{
    Vec3 direction;
    Vec3 first_offset;
    Vec3 second_offset;
    Vec3 first_point;
    Vec3 second_point;
    Vec3 first_next;
    Vec3 second_next;
    float angle;
    float first_depth;
    float second_depth;
    float sine;
    float cosine;
    int dominant;
    int i;

    if (axis->x == 0.0f && axis->y == 0.0f && axis->z == 0.0f) {
        return;
    }
    fn_80211AAC(axis, &direction);
    angle = 360.0f / sides;
    first_depth = -fn_80211B44(first_center, &direction);
    second_depth = -fn_80211B44(second_center, &direction);
    dominant = fn_80179EB8(&direction);

    if ((signed char)dominant == 2 && direction.z < 0.0f) {
        if (first_x > 0.0f) first_x *= 0.5f;
        if (second_x > 0.0f) second_x *= 0.5f;
    }
    if ((signed char)dominant == 1 && direction.y > 0.0f) {
        if (first_x > 0.0f) first_x *= 0.5f;
        if (second_x > 0.0f) second_x *= 0.5f;
    }
    if ((signed char)dominant == 0 && direction.x < 0.0f) {
        if (second_x > 0.0f) first_x *= 0.5f;
        if (second_x > 0.0f) second_x *= 0.5f;
    }

    fn_80179C10(&first_offset, 0.0f, 0.0f, &direction, first_depth, dominant);
    fn_80211A6C(first_center, &first_offset, &first_point);
    fn_80179C10(&first_offset, 0.0f, 0.0f, &direction, second_depth, dominant);
    fn_80211A6C(second_center, &first_offset, &second_point);

    fn_801ED468(0x1B);
    fn_80226D28(0);
    fn_80226D28(2);
    fn_801ED118();
    fn_801EDA7C((void*)0x8030C53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    ((u8*)color)[3] = alpha;
    fn_801ECD74(color);

    sine = fn_80048C2C((sides - 1) * angle);
    cosine = fn_80048C50((sides - 1) * angle);
    fn_80179C10(&first_next, cosine * first_x, sine * first_y,
                &direction, first_depth, dominant);
    fn_80211A48(&first_next, &first_point, &first_next);
    fn_80179C10(&second_next, cosine * second_x, sine * second_y,
                &direction, second_depth, dominant);
    fn_80211A48(&second_next, &second_point, &second_next);
    fn_80226AB4(0x80, 3, sides * 4);

    for (i = 0; (u8)i < sides; i++) {
        sine = fn_80048C2C(i * angle);
        cosine = fn_80048C50(i * angle);
        fn_80179C10(&first_offset, cosine * first_x, sine * first_y,
                    &direction, first_depth, dominant);
        fn_80211A48(&first_offset, &first_point, &first_offset);
        fn_80179C10(&second_offset, cosine * second_x, sine * second_y,
                    &direction, second_depth, dominant);
        fn_80211A48(&second_offset, &second_point, &second_offset);
        fn_80200324(first_offset.x, first_offset.y, first_offset.z);
        fn_80200324(first_next.x, first_next.y, first_next.z);
        fn_80200324(second_next.x, second_next.y, second_next.z);
        fn_80200324(second_offset.x, second_offset.y, second_offset.z);
        first_next = first_offset;
        second_next = second_offset;
    }
    fn_80200320();
    fn_80226D28(1);
}
