typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct DistanceThresholds {
    u16 unused;
    u16 near_distance;
    u16 far_distance;
} DistanceThresholds;

extern DistanceThresholds lbl_8064B730;
extern unsigned int rand(void);
#define rand() ((int)rand())
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3 *, void *
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void* fn_80201B3C();
extern void PSVECSubtract();
extern float PSVECMag(const Vec3 *);

int fn_800CFF04(void *object)
{
    int alternate = rand() & 1;
    Vec3 position_copy;
    Vec3 other_position;
    Vec3 delta;
    Vec3 object_position;
    Vec3 other_position_temp;
    void *other;
    u16 distance;
    int normal_result;
    int alternate_result;

    fn_80201E78(&object_position, object);
    position_copy = object_position;
    other = fn_80201B3C();
    fn_80201E78(&other_position_temp, other);
    other_position = other_position_temp;
    PSVECSubtract(&position_copy, &other_position, &delta);
    distance = (u16)PSVECMag(&delta);

    if (distance < lbl_8064B730.near_distance) {
        alternate_result = 6;
        normal_result = 7;
    } else if (distance < lbl_8064B730.far_distance) {
        alternate_result = 4;
        normal_result = 5;
    } else {
        alternate_result = 4;
        normal_result = 5;
    }

    if (alternate != 0) {
        normal_result = alternate_result;
    }
    return normal_result;
}
