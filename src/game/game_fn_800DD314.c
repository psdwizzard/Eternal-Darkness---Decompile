typedef unsigned char u8;
typedef signed char s8;
typedef int s32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct ColorStep { s8 r, g, b, a; } ColorStep;

typedef struct ObjectContext {
    u8 pad00[0x94];
    s32 unk94;
} ObjectContext;

extern int lbl_8064D18C;

extern void *fn_80201BC8();
extern int fn_8011FB4C();
extern void *fn_80201B8C();
extern void fn_8011F114(Vec3 *, void *);
extern int fn_800DE298();
extern void fn_801261F4(void *);
extern void fn_8012DBE8(void *, int, Color *);
extern void *fn_8012C62C(void *, int, Color, ColorStep, Color, int);
extern void fn_801DDB84(Vec3 *, s32, int, void *);

/* Fade the alpha of an object's model toward a target value in steps. */
void fn_800DD314(void *object, int mode, u8 step, int target) {
    Vec3 position;
    ColorStep delta;
    Color current;
    Color start;
    void *runtime;
    int environment;
    ObjectContext *context;
    u8 diff;
    u8 rem;

    runtime = fn_80201BC8();
    environment = fn_8011FB4C();
    context = fn_80201B8C(object);
    fn_8011F114(&position, runtime);
    if (environment != lbl_8064D18C) {
        return;
    }
    if (fn_800DE298(object) != 0) {
        return;
    }
    fn_801261F4(runtime);
    fn_8012DBE8(runtime, mode, &current);
    start.r = current.r;
    start.g = current.g;
    start.b = current.b;
    delta.r = delta.g = delta.b = 0;
    if (step == 0xFF || step == 0xFD) {
        start.a = target;
        delta.a = 0;
        current.a = target;
        fn_8012C62C(runtime, 0xF, current, delta, start, 4);
        return;
    }
    if (current.a == (u8)target) {
        delta.a = 0;
        start.a = target;
        current.a = target;
        fn_8012C62C(runtime, 0xF, current, delta, start, 4);
        return;
    }
    if (current.a > (u8)target) {
        diff = current.a - target;
        if (diff < step) {
            start.a = target;
            current.a = target;
            current.a = ((u8)target != 0xFF) ? (u8)target + 1 : 0xFF;
            delta.a = -1;
            fn_8012C62C(runtime, mode, current, delta, start, 4);
            return;
        }
        start.a = target;
        rem = diff % step;
        if (rem != 0) {
            current.a -= rem;
        }
        delta.a = -step;
        fn_8012C62C(runtime, mode, current, delta, start, 4);
        return;
    }
    diff = target - current.a;
    if (diff < step) {
        start.a = target;
        current.a = target;
        current.a = ((u8)target == 0) ? 0 : (u8)target - 1;
        delta.a = 1;
        fn_8012C62C(runtime, mode, current, delta, start, 4);
        return;
    }
    start.a = target;
    rem = diff % step;
    if (rem != 0) {
        current.a += rem;
    }
    delta.a = step;
    fn_8012C62C(runtime, mode, current, delta, start, 4);
    fn_801DDB84(&position, context->unk94, 1, runtime);
}
