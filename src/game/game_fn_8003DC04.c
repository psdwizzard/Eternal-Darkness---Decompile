typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct RuntimeState RuntimeState;

typedef struct ObjectInfo {
    u8 padding[0x8C];
    RuntimeState *state;
} ObjectInfo;

typedef struct Object80201C48 Object80201C48;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object Object;

extern void *fn_80201B8C(u8 *object);
extern void *fn_80201B94(u8 *object);
extern int fn_800CAF7C(void *object);
extern int fn_8011EB04(Object *object);
extern int fn_8003CD0C(void *object, void *target, void *context);
extern int fn_801296F8(void *owner, int value);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern int fn_80201B54(int *object);
extern int fn_800359A0(void *source, void *requested);
extern void *fn_80201C48(Object80201C48 *object);
extern int fn_800BDEE4(int object, RuntimeState *state);
extern void fn_80201D2C(Object80201D2C *object, int value);
extern void fn_80201D14(Object80201D14 *object, u8 value);

int fn_8003DC04(u8 *object, Vec3 *target, void *context,
                u32 flags, u32 mask, int enabled)
{
    Vec3 position;
    ObjectInfo *info;
    Object80201C48 *relation;

    info = fn_80201B8C(object);
    relation = fn_80201B94(object);
    if (fn_800CAF7C(object) == 0 && enabled != 0) {
        if (fn_8011EB04((Object *)target) == 1 && (flags & 0x1F) == 0) {
            if (fn_8003CD0C(object, target, context) != 0) {
                fn_801296F8(target, 0x1FD70);
                return 1;
            }
            return 0;
        }
        if ((u8)flags == 0) {
            return fn_8003CD0C(object, target, context);
        }
    } else if ((flags & mask) == 0) {
        fn_8011F114(&position, target);
        fn_80201B54((int *)object);
        if (fn_800359A0(object, 0) != 0) {
            if ((int)fn_80201C48(relation) != 0) {
                fn_800BDEE4((int)object, info->state);
            }
            fn_80201D2C((Object80201D2C *)object, 3);
            fn_80201D14((Object80201D14 *)object, 1);
            return 1;
        }
    }
    return 0;
}
