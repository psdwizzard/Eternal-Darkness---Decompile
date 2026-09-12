typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const float lbl_806515AC;
extern const float lbl_806515B0;
extern float fn_8012B7D0(void *, Vec3 *);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);

int fn_80204434(void *object, Vec3 *position, float *delta_out, float tolerance)
{
    Vec3 copy = *position;
    float target;
    float scaled_tolerance = tolerance * lbl_806515AC;
    int result = 1;
    float current;
    float delta;

    target = fn_8012B7D0(object, &copy);
    current = fn_8012B750(object);
    fn_8017A12C(&delta, current, target);
    if (delta_out != 0) {
        *delta_out = delta;
    }
    if ((delta < lbl_806515B0 ? -delta : delta) > scaled_tolerance) {
        result = 0;
    }
    return result;
}
