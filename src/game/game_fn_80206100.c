typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef float Matrix34[3][4];

typedef struct QueryResult {
    u8 pad[0x14];
    Vec3 position;
    u8 pad2[8];
} QueryResult;

extern const Vec3 lbl_8023B8AC;
extern const Vec3 lbl_8023B8B8;
extern float lbl_806515EC;
extern float lbl_806515F8;
extern float lbl_80651600;
extern float lbl_80651604;

extern void fn_801F68B0(Vec3 *);
extern void fn_801F68F8(Vec3 *);
extern void fn_80211A6C(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211B64(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern float fn_80211B08(const Vec3 *);
extern float fn_80211B44(const Vec3 *, const Vec3 *);
extern void fn_80211A90(const Vec3 *, Vec3 *, float);
extern void *fn_8011FE34(void *);
extern void fn_8012B7A0(void *, float);
extern void fn_8012CDF0(void *, int, Vec4, int);
extern int fn_8011F598(void *, int, int, int, QueryResult *, int);
extern float fn_800490E8(float, float);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_802114E0(Matrix34, const Vec4 *);
extern void fn_80211710(Matrix34, const Vec3 *, Vec3 *);
extern void fn_8017A34C(const Vec4 *, const Vec4 *, Vec4 *);
extern void fn_8012CF08(void *, int, Vec4, Vec4, int, int, float);
extern void fn_8011FABC(void *, int, int);

void fn_80206100(void *object)
{
    QueryResult query;
    Matrix34 rotation_matrix;
    Vec4 object_rotation;
    Vec3 direction;
    Vec3 side;
    Vec3 random_a;
    Vec3 random_b;
    Vec3 up;
    Vec4 first_rotation;
    Vec4 second_rotation;
    Vec4 combined_rotation;
    Vec4 final_rotation_a;
    Vec3 cross;
    Vec3 second_cross;
    Vec3 query_axis;
    Vec3 transformed;
    Vec4 final_rotation_b;
    Vec3 random_temp_a;
    Vec3 random_temp_b;
    float angle;
    float dot;

    fn_801F68B0(&random_temp_a);
    random_a = random_temp_a;
    fn_801F68F8(&random_temp_b);
    random_b = random_temp_b;
    up = lbl_8023B8AC;
    fn_80211A6C(&random_b, &random_a, &direction);
    fn_80211B64(&direction, &up, &side);
    fn_80211B64(&side, &direction, &up);
    fn_80211AAC(&up, &up);

    object_rotation = *(Vec4 *)fn_8011FE34(object);
    fn_8012B7A0(object, lbl_806515F8);
    fn_8012CDF0(object, 0xF, object_rotation, 1);

    if (fn_8011F598(object, 0x13, 0, -1, &query, 1) == -1) {
        return;
    }

    query_axis = lbl_8023B8B8;
    fn_80211B64(&query.position, &query_axis, &side);
    fn_80211B64(&side, &query.position, &query_axis);
    fn_80211AAC(&query_axis, &query_axis);
    fn_80211B64(&query_axis, &up, &cross);
    angle = fn_80211B08(&cross);
    if ((angle < lbl_806515F8 ? -angle : angle) > lbl_806515EC) {
        fn_80211AAC(&cross, &cross);
        dot = fn_80211B44(&query_axis, &up);
        fn_8017A244(&cross, &first_rotation, fn_800490E8(angle, dot));
        fn_802114E0(rotation_matrix, &first_rotation);
        fn_80211AAC(&query.position, &query.position);
        fn_80211710(rotation_matrix, &query.position, &transformed);
        fn_80211AAC(&transformed, &transformed);
        fn_80211A90(&direction, &direction, lbl_80651600);
        fn_80211B64(&transformed, &direction, &second_cross);
        angle = fn_80211B08(&second_cross);

        if ((angle < lbl_806515F8 ? -angle : angle) > lbl_806515EC) {
            fn_80211AAC(&second_cross, &second_cross);
            fn_8017A244(&second_cross, &second_rotation,
                        fn_800490E8(angle, fn_80211B44(&transformed, &direction)));
            fn_8017A34C(&second_rotation, &first_rotation, &combined_rotation);
            fn_8017A34C(&combined_rotation, &object_rotation, &final_rotation_a);
            fn_8012CF08(object, 0xF, object_rotation, final_rotation_a,
                        1, 0, lbl_80651604);
            fn_8011FABC(object, 0, 0x10);
        } else {
            fn_8017A34C(&first_rotation, &object_rotation, &final_rotation_b);
            fn_8012CF08(object, 0xF, object_rotation, final_rotation_b,
                        1, 0, lbl_80651604);
            fn_8011FABC(object, 0, 0x10);
        }
    }
}
