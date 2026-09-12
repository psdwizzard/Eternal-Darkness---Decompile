typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object {
    u8 pad00[4];
    u32 flags;
    u8 pad08[0xB8];
    int owner;
} Object;

extern void* fn_801A717C(void);
extern int fn_80201B54(void*);
extern void fn_801A74A0(void*, int);
extern void fn_801A74A8(void*, int);
extern void fn_801A7538(void*, int);
extern int fn_801CEB2C(u32);
extern int fn_801D38E8(u32);
extern int fn_80035628(void*);
extern int fn_801D1B10(int, int, int, int);
extern int fn_80201B44(int);
extern int fn_80071DD8(void);
extern void fn_801A7518(void*, int);
extern void fn_801A7588(void*, int);
extern void fn_80201E78(Vec3*, void*);
extern u32 fn_80179004(Vec3*, Vec3*);
extern void fn_801A764C(void*, Vec3*);
extern void fn_801A74D8(void*, u32);
extern void fn_801A7668(void*, int);
extern void fn_801A7670(void*, int);
extern void fn_8020104C(int, int, int, int, float);
extern float lbl_806510E0;

int fn_801D76A8(void* item, Object* object, s16* first, s16* second)
{
    int result;
    int kind;
    void* effect;
    u8 count;
    Vec3 item_position;
    Vec3 first_position;
    Vec3 second_position;
    Vec3 midpoint;
    u32 first_distance;
    u32 second_distance;
    u32 midpoint_distance;
    Vec3* position;

    effect = fn_801A717C();
    result = 0;
    if (effect != 0) {
        kind = fn_80201B54(item);
        fn_801A74A0(effect, object->owner);
        fn_801A74A8(effect, kind);
        fn_801A7538(effect, 1);
        count = (u8)(((s16)fn_801CEB2C(object->flags) >> 1) + 1);
        result = fn_801D38E8(object->flags);
        {
            int item_value = fn_80035628(item);
            result = fn_801D1B10(5, item_value, result, count);
        }
        if (kind != fn_80201B44(result) && fn_80071DD8() != 0)
            fn_801A7518(effect, 0);
        else
            fn_801A7518(effect, result);
        fn_801A7588(effect, 2);

        fn_80201E78(&item_position, item);
        first_position.x = first[0];
        first_position.y = first[1];
        first_position.z = first[2];
        second_position.x = second[0];
        second_position.y = second[1];
        second_position.z = second[2];
        first_distance = fn_80179004(&item_position, &first_position);
        second_distance = fn_80179004(&item_position, &second_position);
        midpoint.x = first[0] + ((second[0] - first[0]) >> 1);
        midpoint.y = first[1] + ((second[1] - first[1]) >> 1);
        midpoint.z = first[2] + ((second[2] - first[2]) >> 1);
        midpoint_distance = fn_80179004(&item_position, &midpoint);
        if (first_distance < second_distance) {
            if (first_distance < midpoint_distance)
                position = &first_position;
            else
                position = &midpoint;
        } else if (second_distance < midpoint_distance) {
            position = &second_position;
        } else {
            position = &midpoint;
        }
        fn_801A764C(effect, position);
        fn_801A74D8(effect, 0x1800);
        fn_801A7668(effect, fn_801D38E8(object->flags));
        fn_801A7670(effect, count);
        fn_8020104C(237, object->owner, kind, (int)effect, lbl_806510E0);
    }
    return result;
}
