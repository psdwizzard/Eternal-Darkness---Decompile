typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern unsigned int lbl_8064D5A8;
extern const float lbl_8064E920;
extern const float lbl_8064E93C;
extern const float lbl_8064E940;
extern const float lbl_8064E944;
extern const float lbl_8064E948;
extern const float lbl_8064E94C;

extern void* fn_80201B94();
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern void *fn_80201C48(void *object);
extern void *fn_80201814();
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_80079008(void *object, void *target);
extern int fn_8007930C(void *object, void *target, void *extra);
extern void fn_800359A0(void *object, int value);
extern void fn_8011F114();
extern unsigned int fn_80178E94(Vec3 *first, Vec3 *second);
extern int fn_800CA7D4(void *owner, void *object, void *argument,
                      void *target, int type, int enabled);
extern unsigned long long fn_8020123C();
extern int fn_8003E0E4(void *object, Vec3 *position, float first,
                      float second, int enabled);
extern int fn_80204434(void *object, Vec3 *position, float value,
                      float *result);
#define FN_80128E30_RETURN void*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern void fn_80128C3C(void *object, float value);
extern int fn_8012AFC4(void *object);
extern void fn_8012B344(void*);
extern int fn_801290D0(void *object);
extern void fn_80128F74(void *object, int flags);
extern void fn_80129928(void *object, Vec3 *position);
extern void fn_800BE70C(void *object, Vec3 *position, int type, int zero,
                       float first, float second, float third);
extern void fn_8012976C(void *object, int type, int flags, Vec3 *position,
                       float value);
extern int fn_800BE2CC(void *object, void *argument, Vec3 *position);
extern void fn_800BE390(void *object, void *argument);

int fn_80079D24(void *object, void *target, void *owner, void *argument,
                void *extra)
{
    Vec3 alternate_position;
    Vec3 target_position;
    Vec3 object_position;
    void *handle = fn_80201B94(object);
    void *state = *(void **)((char *)fn_80201B8C(object) + 0xC);
    int target_state;
    void *linked;
    void *linked_position;
    int distance;
    int visible;
    int valid;
    float vertical;
    float speed;
    float side;

    fn_8011F114(&object_position, target);
    target_state = fn_80079008(object, target);
    if ((lbl_8064D5A8 & 0xF) == 0)
        fn_800359A0(object, 0);

    linked = fn_80201814(fn_80201C48(handle));
    linked_position = linked != 0 ? fn_80201BC8(linked) : 0;

    if (fn_800CA7D4(owner, object, argument, target, 0x19, 1)) {
        if (target_state != 0) {
            *(unsigned short *)((char *)state + 0x3C) |= 2;
            fn_8020123C(0xE1, owner, owner, 0);
            return 1;
        }
        return fn_8007930C(object, target, extra);
    }

    if (linked == 0 || linked_position == 0)
        goto finish;

    fn_8011F114(&target_position, linked_position);
    distance = fn_80178E94(&object_position, &target_position);
    valid = fn_8003E0E4(object, &target_position, lbl_8064E93C,
                       lbl_8064E93C, 1);
    visible = fn_80204434(target, &target_position, lbl_8064E940, &side);
    vertical = object_position.z - target_position.z;
    if (vertical < lbl_8064E920)
        vertical = -vertical;

    if (*(signed char *)((char *)state + 0x41) != 0)
        speed = lbl_8064E944;
    else if (target_state != 0)
        speed = lbl_8064E948;
    else
        speed = lbl_8064E948;

    fn_80128C3C(fn_80128E30(target), speed);

    if (distance < 0x127 && visible &&
        (valid != 0 || vertical < lbl_8064E94C)) {
        if (target_state != 0) {
            fn_8020123C(0xE1, owner, owner, 0);
            return 1;
        }
        return fn_8007930C(object, target, extra);
    }

    if (distance < 0x154 && valid) {
        if (target_state == 0) {
            if (distance < 0x122 && side > lbl_8064E940) {
                if (fn_8012AFC4(target))
                    fn_8012B344(target);
                fn_800BE70C(target, &target_position, 0x7A, 0, speed,
                            lbl_8064E940, lbl_8064E940);
            } else if (fn_8012AFC4(target)) {
                fn_80128F74(target, fn_801290D0(target) & ~7);
                fn_80129928(target, &target_position);
            } else {
                fn_8012976C(target, 0x7A, 0x31, &target_position, speed);
            }
        } else if (fn_80204434(target, &target_position, lbl_8064E940, 0)) {
            fn_8020123C(0xE1, owner, owner, 0);
            return 1;
        } else if (fn_8012AFC4(target)) {
            fn_80129928(target, &target_position);
            fn_80128F74(target, fn_801290D0(target) & ~7);
        } else {
            fn_8012976C(target, 2, 0x31, &target_position, speed);
        }
        return 0;
    }

    if (fn_800BE2CC(object, argument, &alternate_position)) {
        int type = target_state != 0 ? 2 : 0x7A;
        if (target_state == 0 && distance > 0x17C) {
            fn_8020123C(0x6A, owner, owner, 0);
            return 1;
        }
        if (fn_80178E94(&object_position, &alternate_position) < 100) {
            fn_800BE390(object, argument);
        } else if (fn_8012AFC4(target)) {
            fn_80129928(target, &alternate_position);
            fn_80128F74(target, fn_801290D0(target) & ~7);
        } else {
            fn_8012976C(target, type, 0x31, &alternate_position, speed);
        }
        return 0;
    }

finish:
    fn_80201D2C(object, 1);
    fn_80201D14(object, 1);
    return 1;
}
