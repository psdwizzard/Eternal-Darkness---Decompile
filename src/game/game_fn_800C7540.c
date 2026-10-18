typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void *fn_80201B94(void *object);
extern void *fn_80201C48(void *relation);
extern int fn_80201EB8(void *object);
extern int rand(void);
extern void *fn_80201814(int identifier);
extern void fn_80201E78(void *destination, void *object);
extern void *fn_80201BC8(void *object);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern int fn_8011EB04(void *runtime);
extern float fn_801790A4(float x1, float y1, float x2, float y2);
extern float fn_8012B7D0(const void *runtime, const void *position);
extern float fn_8012B750(void *runtime);
extern void fn_8017A12C(float *result, float current, float target);
extern int fn_80201B54(void *object);
extern int fn_80128EAC(void *runtime);
extern unsigned long long fn_8020123C(int kind, int source, int target, int value);
extern int lbl_8064D18C;
extern unsigned int lbl_8064D5A8;
extern float lbl_8064F214;
extern float lbl_8064F218;
extern float lbl_8064F21C;
extern float lbl_8064F220;

void fn_800C7540(void *object)
{
    Vec3 target_position;
    Vec3 position;
    Vec3 query_position;
    float angle;
    float distance_limit;
    float facing;
    float magnitude;
    int target_id;
    void *target;
    void *runtime;
    void *target_runtime;
    int source_id;

    target_id = (int)fn_80201C48(fn_80201B94(object));
    if (lbl_8064D18C == fn_80201EB8(object) &&
        (lbl_8064D5A8 & 0x7F) == 0 && (rand() & 1) == 0) {
        distance_limit = lbl_8064F214;
        target = fn_80201814(target_id);
        if (target != 0) {
            fn_80201E78(&target_position, target);
            runtime = fn_80201BC8(object);
            fn_8011F114(&position, runtime);
            if (fn_8011EB04(runtime) == 0xFB) {
                distance_limit = lbl_8064F218;
            }
            if (fn_801790A4(target_position.x, target_position.y,
                           position.x, position.y) < distance_limit) {
                query_position = target_position;
                facing = fn_8012B7D0(runtime, &query_position);
                fn_8017A12C(&angle, fn_8012B750(runtime), facing);
                magnitude = angle;
                if (magnitude < lbl_8064F21C) {
                    magnitude = -magnitude;
                }
                if (magnitude <= lbl_8064F220) {
                    target_runtime = fn_80201BC8(target);
                    source_id = fn_80201B54(object);
                    if (fn_80128EAC(target_runtime) != 0x29) {
                        fn_8020123C(0xD7, source_id, source_id, target_id);
                    }
                }
            }
        }
    }
}
