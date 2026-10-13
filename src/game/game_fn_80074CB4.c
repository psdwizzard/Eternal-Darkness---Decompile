typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct AiWork {
    f32 homeDistance;
    f32 travelDistance;
    u8 pad08[0x190 - 8];
    Vec3 homePosition;
    u8 pad19C[0x1BF - 0x19C];
    u8 waitCount;
} AiWork;

typedef struct RuntimeState {
    u8 pad00[0xAC];
    s32 pool_index;
    s32 slot_index;
} RuntimeState;

typedef struct AiOwner {
    u8 pad00[0x44];
    AiWork *work;
    u8 pad48[0x8C - 0x48];
    RuntimeState *runtime;
} AiOwner;

/* Opaque types used by the setters and movement routines. */
typedef struct Object80201C48 Object80201C48;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;
typedef struct Owner Owner;
typedef struct Vec Vec;

extern void *fn_80201B94(u8 *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201C48(Object80201C48 *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern s32 fn_80066D04(void *, s32);
extern void fn_80201D2C(Object80201D2C *, s32);
extern void fn_80201D14(Object80201D14 *, u8);
extern s32 fn_800359A0(void *, void *);
extern s32 fn_802045AC(void *, Vec3 *);
extern u32 fn_80178E94(const f32 *, const f32 *);
extern f32 fn_8011F6F8(void *);
extern f32 fn_8012B7D0(const void *, const void *);
extern f32 fn_8012B750(void *);
extern void fn_8017A12C(f32 *, f32, f32);
extern s32 fn_8003E1F0(void *, Vec3 *, s32, f32);
extern u8 fn_80204578(void *, const Vec3 *);
/* These attack routines ignore the extra event argument. */
extern s32 fn_8007381C();
extern s32 fn_80073C64();
extern void fn_8012B344(void *);
extern s32 fn_800BDEE4(s32, RuntimeState *);
extern s32 fn_800BE260(void *, RuntimeState *);
extern s32 fn_800BE2CC(void *, RuntimeState *, void *);
extern void fn_800BE390(void *, RuntimeState *);
extern void fn_801E7DCC(const char *, ...);
extern s32 fn_8012AFC4(void *);
extern s32 fn_80129928(void *, Vec *);
extern u8 *fn_8012976C(Owner *, s32, s32, Vec3 *, f32);
extern char lbl_802446C0[];
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
extern f32 lbl_8064E870;
extern f32 lbl_8064E894;
extern f32 lbl_8064E89C;
extern f32 lbl_8064E8A0;

static inline f32 AngleMagnitude(f32 angle)
{
    if (angle < lbl_8064E870) {
        angle = -angle;
    }
    return angle;
}

s32 fn_80074CB4(void *object, void *resource, s32 name,
                 RuntimeState *runtime, void *event)
{
    Vec3 targetPosition;
    Vec3 alternatePosition;
    Vec3 resourcePosition;
    Vec3 queryPosition;
    f32 angle;
    f32 speed;
    f32 facing;
    s32 reachable;
    AiWork *work;
    AiOwner *owner;
    void *target;
    u32 distance;
    u32 homeDistance;
    s32 result;

    result = 0;
    target = fn_80201B94(object);
    fn_8011F114(&resourcePosition, resource);
    owner = fn_80201B8C(object);
    work = owner->work;
    if (fn_80066D04(object, 0) == 0) {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    }
    if ((lbl_8064D5A8 & 7) == 0) {
        fn_800359A0(object, 0);
    }
    if ((s32)fn_80201C48(target) != 0) {
        if (work->waitCount != 0) {
            work->waitCount--;
        }
        fn_802045AC(object, &targetPosition);
        distance = fn_80178E94(&resourcePosition.x, &targetPosition.x);
        homeDistance = fn_80178E94(&work->homePosition.x, &resourcePosition.x);
        speed = fn_8011F6F8(resource);
        speed *= lbl_8064E894;
        queryPosition = targetPosition;
        facing = fn_8012B7D0(resource, &queryPosition);
        fn_8017A12C(&angle, fn_8012B750(resource), facing);
        reachable = fn_8003E1F0(object, &targetPosition, 1, speed);
        if (distance < 225 && fn_80204578(object, &targetPosition) != 0 &&
            reachable != 0) {
            if (work->waitCount == 0) {
                if (fn_8007381C(object, resource, event) == 0) {
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            } else {
                fn_8012B344(resource);
            }
        } else if (distance > (u32)((s32)work->homeDistance + 50)) {
            if ((s32)fn_80201C48(target) != 0) {
                fn_800BDEE4((s32)object, owner->runtime);
            }
            fn_80201D2C(object, 3);
            fn_80201D14(object, 1);
        } else if ((f32)homeDistance >= work->travelDistance) {
            if (distance > 800 || fn_80073C64(object, resource, event) == 0) {
                fn_80201D2C(object, 45);
                fn_80201D14(object, 1);
            }
        } else if (fn_800BE260(object, runtime) != 0) {
            if (lbl_8064D18C != 0x53 && lbl_8064D18C != 0x1B &&
                lbl_8064D18C != 0x7B && lbl_8064D18C != 0x159 &&
                lbl_8064D18C != 0x34) {
                fn_801E7DCC(lbl_802446C0, name);
            }
            result = 1;
            fn_8012B344(resource);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
        } else if (distance < 118 && AngleMagnitude(angle) <= lbl_8064E89C) {
            if (fn_8007381C(object, resource, event) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            result = 1;
        } else if (distance < 700 && reachable != 0) {
            if (fn_8012AFC4(resource) != 0) {
                fn_80129928(resource, (Vec *)&targetPosition);
            } else {
                fn_8012976C(resource, 2, 0x21, &targetPosition, lbl_8064E8A0);
            }
        } else if (fn_800BE2CC(object, runtime, &alternatePosition) != 0) {
            if (fn_80178E94(&resourcePosition.x, &alternatePosition.x) < 80) {
                fn_800BE390(object, runtime);
            } else if (fn_8012AFC4(resource) != 0) {
                fn_80129928(resource, (Vec *)&alternatePosition);
            } else {
                fn_8012976C(resource, 2, 0x21, &alternatePosition, lbl_8064E8A0);
            }
        } else {
            result = 1;
            fn_8012B344(resource);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
        }
    } else {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    }
    return result;
}
