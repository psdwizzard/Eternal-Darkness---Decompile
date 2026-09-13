typedef int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ObjectData {
    unsigned char pad00[0x14];
    s32 reference;
    unsigned char pad18[0xC];
    Vec3 position;
} ObjectData;

extern void *fn_80201BC8(void *object);
extern ObjectData *fn_80201B94(void *object);
extern s32 fn_80201B54(void *object);
extern void fn_8011F114(Vec3 *dest, void *source);
extern void fn_801F68B0(Vec3 *position);
extern void *fn_80201814(s32 reference);

s32 fn_802045AC(void *object, Vec3 *position)
{
    Vec3 object_position;
    Vec3 copied_position;
    Vec3 global_position;
    Vec3 target_position;
    void *transform;
    void *target_transform;
    ObjectData *data;
    s32 result = 1;

    transform = fn_80201BC8(object);
    data = fn_80201B94(object);
    fn_80201B54(object);
    fn_8011F114(&object_position, transform);

    if (data->reference == -1) {
        position->x = data->position.x;
        position->y = data->position.y;
        position->z = data->position.z;
    } else if (data->reference == -2) {
        fn_801F68B0(&global_position);
        *position = global_position;
        position->z = object_position.z;
    } else {
        void *target = fn_80201814(data->reference);
        if (target != 0) {
            target_transform = fn_80201BC8(target);
            fn_8011F114(&target_position, target_transform);
            copied_position = target_position;
            position->x = copied_position.x;
            position->y = copied_position.y;
            position->z = copied_position.z;
        } else {
            result = 0;
        }
    }

    return result;
}
