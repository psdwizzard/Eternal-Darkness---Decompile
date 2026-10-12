typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const Vec3 lbl_80239854;
extern const float lbl_8064F110;
extern const float lbl_8064F1CC;

extern void *fn_801A7778(void *object);
extern int fn_800C44C0(void *object, void *target, void *actor, Vec3 *position, int *found);
extern void fn_8003B0BC(void *object, Vec3 *normal_out, Vec3 *position_out, int context, int transform, int use_transform);
extern void fn_80211A6C(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern float fn_80211B08(const Vec3 *v);
extern float fn_80211B44(const Vec3 *a, const Vec3 *b);
extern void fn_80211B64(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void fn_8012B6FC(void *object, Vec3 *in, Vec3 *out);
extern float fn_800490E8(float y, float x);

int fn_800C4238(void *object, void *target, void *actor, void *runtime) {
    Vec3 down = lbl_80239854;
    Vec3 up;
    Vec3 surface;
    Vec3 normal;
    Vec3 position;
    Vec3 offset;
    Vec3 side;
    Vec3 axis;
    Vec3 cross;
    int found;
    int result;
    void *model;
    float length;
    float dot;

    result = 0;
    model = fn_801A7778(runtime);
    if (fn_800C44C0(object, actor, runtime, &position, &found) != 0) {
        fn_8003B0BC(model, &surface, &normal, (int)runtime, (int)target, 0);
        fn_80211A6C(&position, &surface, &offset);
        if (fn_80211B44(&normal, &offset) > lbl_8064F110) {
            fn_80211B64(&normal, &offset, &side);
            fn_8012B6FC(target, &down, &up);
            fn_80211B64(&normal, &up, &axis);
            fn_80211B64(&side, &axis, &cross);
            length = fn_80211B08(&cross);
            dot = fn_80211B44(&side, &axis);
            if (fn_800490E8(length, dot) > lbl_8064F1CC) {
                result = 1;
            }
        }
    }
    return result;
}
