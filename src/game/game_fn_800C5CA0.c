typedef signed short s16;
typedef unsigned char u8;

typedef struct Layout {
    char pad0[0x10];
    s16 left;
    s16 right;
    s16 total;
} Layout;

typedef struct Target {
    char pad0[0x10];
    int id;
} Target;

typedef struct Info {
    Layout *layout;
    char pad4[0x88];
    Target *target;
} Info;

extern int lbl_8064B718;
extern int lbl_8064B724;
extern const float lbl_8064F1EC;

extern void *fn_80201BC8();
extern Info *fn_80201B8C(void *);
extern u8 fn_80128EE4(void *);
extern int fn_80038308(void *, int, s16 *);
extern int fn_80038464(void *, int, s16 *);
extern void fn_800389E0(void *, int, s16, int);
extern void fn_8011FAFC(void *, int);
extern int fn_80201B54(void *);
extern unsigned long long fn_8020123C(int, int, int, float *);

void fn_800C5CA0(void *object)
{
    void *runtime;
    Info *info;
    u8 flags;
    s16 cur;
    s16 max;
    float ratio;
    Layout *layout;
    s16 threshold;
    s16 step;

    runtime = fn_80201BC8();
    info = fn_80201B8C(object);
    if (runtime != 0) {
        flags = fn_80128EE4(runtime);
    } else {
        flags = 0;
    }
    if (info != 0 && info->target != 0 && info->layout != 0 &&
        fn_80038308(object, 3, &cur) != 0 && fn_80038464(object, 3, &max) != 0) {
        layout = info->layout;
        threshold = lbl_8064F1EC * max;
        step = layout->total;
        step = step - ((flags & 8) ? layout->left : 0);
        step -= (flags & 2) ? layout->right : 0;
        if (cur < threshold && step > 0) {
            step >>= 1;
        }
        cur += step;
        cur = cur < max ? cur : max;
        cur = cur > 0 ? cur : 0;
        if (cur <= 10) {
            lbl_8064B718 = 0;
        } else if ((lbl_8064B724 == 0 || lbl_8064B718 == 0) && cur >= threshold) {
            lbl_8064B724 = 1;
            lbl_8064B718 = 1;
        }
        fn_8011FAFC(runtime, lbl_8064B724);
        fn_800389E0(object, 3, cur, 1);
        ratio = (float)cur / (float)max;
        fn_8020123C(0x27, fn_80201B54(object), info->target->id, &ratio);
    }
}
