typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

extern const Vec3 lbl_8023B8C4;

extern void fn_801F68B0(Vec3 *);
extern void fn_801F68F8(Vec3 *);
extern void fn_8012CEA4(void *, int, Vec4 *);
extern void fn_80211A6C(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211B64(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8017A34C(const Vec4 *, const Vec4 *, Vec4 *);
extern void fn_8012CDF0(void *, int, Vec4, int);

void fn_802064F4(void *object, const Vec4 *base_rotation, float angle)
{
    Vec3 direction;
    Vec3 side;
    Vec3 random_a;
    Vec3 random_b;
    Vec3 up;
    Vec4 random_rotation;
    Vec4 result_rotation;
    Vec4 object_rotation;
    Vec3 random_temp_a;
    Vec3 random_temp_b;

    fn_801F68B0(&random_temp_a);
    random_a = random_temp_a;
    fn_801F68F8(&random_temp_b);
    random_b = random_temp_b;
    up = lbl_8023B8C4;
    fn_8012CEA4(object, 0xF, &object_rotation);
    fn_80211A6C(&random_b, &random_a, &direction);
    fn_80211B64(&direction, &up, &side);
    fn_80211B64(&side, &direction, &up);
    fn_80211AAC(&up, &up);
    fn_8017A244(&up, &random_rotation, angle);
    fn_8017A34C(&random_rotation, base_rotation, &result_rotation);
    fn_8012CDF0(object, 0xF, result_rotation, 1);
}
