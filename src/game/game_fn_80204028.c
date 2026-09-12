#pragma use_lmw_stmw on

typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const volatile Vec3 lbl_8023B880;

extern void *fn_80201B9C(void);
extern int fn_80201B54(void *object);
extern void *fn_80201BC0(void *object);
extern void *fn_80201BC8(void *object);
extern int fn_80201EB8(void *object);
extern void fn_8011F114(Vec3 *position, void *transform);
extern u32 fn_80178E94(Vec3 *first, Vec3 *second);
extern void fn_8020123C(int type, int source, int target, int value);

int fn_80204028(void *object, u32 distance, int unused, int value)
{
    void *current;
    void *transform;
    Vec3 source_position;
    Vec3 candidate_position;
    Vec3 source_temporary;
    Vec3 candidate_temporary;
    Vec3 fallback;
    Vec3 *position;
    int environment;
    int source;
    int count;

    current = fn_80201B9C();
    transform = fn_80201BC8(object);
    fn_8011F114(&source_temporary, transform);
    source_position = source_temporary;
    environment = fn_80201EB8(object);
    source = fn_80201B54(object);
    count = 0;

    while (current != 0) {
        transform = fn_80201BC8(current);
        if (transform != 0) {
            fn_8011F114(&candidate_temporary, transform);
            position = &candidate_temporary;
        } else {
            fallback = lbl_8023B880;
            position = &fallback;
        }
        candidate_position = *position;

        if (fn_80201EB8(current) == environment && transform != 0 &&
            object != current &&
            fn_80178E94(&source_position, &candidate_position) < distance) {
            fn_8020123C(0x5A, source, fn_80201B54(current), value);
            count++;
        }
        current = fn_80201BC0(current);
    }

    return count;
}
