typedef signed int s32;
typedef unsigned char u8;
typedef float f32;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct EventState {
    u8 pad0[0x60];
    s32 unk60;
} EventState;

extern f32 lbl_8064E4EC;
extern f32 lbl_8064E4F0;
extern f32 lbl_8064E4F4;

extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern EventState **fn_80201B8C();
extern void fn_8011E174(s32 index, s32 value);
extern unsigned long long fn_8020123C();
extern void *fn_80201814();
extern Vec3 fn_80201E78(void *);
extern f32 fn_8012B7D0(void *, Vec3);
extern f32 fn_8012B750(void *);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_800BE86C(void *, Vec3 *, s32, s32, f32);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_801E8328(s32, s32);

s32 fn_80055774(void *context, void *event)
{
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);
    int owner = fn_80201B54(context);
    EventState **state = fn_80201B8C(context);

    if (kind == 1) {
        fn_8011E174(0x80, 1);
        fn_8020123C(0x2D, owner, owner, 0);
        return 1;
    }
    if (kind == 3) {
        void *target = fn_80201814((*state)->unk60);
        Vec3 pos = fn_80201E78(target);
        f32 dist = fn_8012B7D0(object, pos);
        f32 angle;
        f32 delta;

        fn_8017A12C(&angle, fn_8012B750(object), dist);
        delta = angle;
        if (delta < lbl_8064E4EC) {
            delta = -delta;
        }
        if (delta > lbl_8064E4F0) {
            fn_800BE86C(object, &pos, 2, 0, lbl_8064E4F4);
        }
        return 1;
    }
    if (kind == 6) {
        fn_80201D2C(context, 1);
        fn_80201D14(context, 1);
        return 1;
    }
    if (kind == 92) {
        fn_80201D2C(context, 1);
        fn_80201D14(context, 1);
        return 1;
    }
    if (kind == 2) {
        fn_801E8328(0x1E, 0x80);
        (*state)->unk60 = 0;
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 135) return 1;
    if (kind == 11) return 1;
    if (kind == 30) return 1;
    if (kind == 41) return 1;
    if (kind == 42) return 1;
    if (kind == 43) return 1;
    if (kind == 44) return 1;
    if (kind == 40) return 1;
    if (kind == 39) return 1;
    if (kind == 105) return 1;
    if (kind == 125) return 1;
    if (kind == 59) return 1;
    if (kind == 147) return 1;
    if (kind == 175) return 1;
    if (kind == 103) return 1;
    if (kind == 133) return 1;
    if (kind == 202) return 1;
    return (u8)(kind == 31);
}
