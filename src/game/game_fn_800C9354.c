typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern Vec3 fn_80201E78(void *object);
extern void PSVECSubtract(const Vec3 *first, const Vec3 *second, Vec3 *result);
extern float PSVECMag(const Vec3 *value);
extern float lbl_8064F294;

int fn_800C9354(void *first, void *second, void *third)
{
    Vec3 third_position = fn_80201E78(third);
    Vec3 second_position = fn_80201E78(second);
    Vec3 first_position = fn_80201E78(first);
    Vec3 first_delta;
    Vec3 second_delta;
    float first_distance;

    PSVECSubtract(&third_position, &second_position, &first_delta);
    PSVECSubtract(&third_position, &first_position, &second_delta);
    first_distance = PSVECMag(&first_delta);
    return PSVECMag(&second_delta) - first_distance >= lbl_8064F294;
}
