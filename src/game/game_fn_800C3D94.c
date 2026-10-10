typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#define NULL ((void *)0)

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern void *fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C48(void *);
extern void *fn_80201814();
extern void *fn_80200C38();
extern u32 fn_801A74C0(void *);
extern u32 fn_801A7570(void *);
extern u16 fn_801A7580(void *);
extern void *fn_80201B9C();
extern void *fn_80204844(void *, int);
extern void *fn_8006D444(void);
extern void fn_800C43AC(Vec3 *, void *);
extern int fn_8006D344(void *, int, int);
extern int fn_80088528(void *, Vec3 *);
extern int fn_800BE86C(void *, Vec3 *, int, f32 *, f32);
extern void fn_800C3FE4(void *, void *, void *);
extern int fn_800C4238(void *, void *, void *, void *);
extern int fn_8012915C(void *);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_801A74D8(void *, u32);
extern int fn_801A77B0(void *);
extern void fn_801A75A0(void *, u16);

extern f32 lbl_8064F110;
extern f32 lbl_8064F1C4;
extern f32 lbl_8064F1C8;

int fn_800C3D94(void *object, void *event, int *result) {
    Vec3 pos;
    f32 dist;
    void *self;
    void *owner;
    int hit;
    void *target;
    void *effect;
    u32 state;
    u32 flags;
    u16 count;
    void *model;
    int id;

    self = fn_80201B94(object);
    owner = fn_80201BC8(object);
    fn_80201C48(self);
    hit = 0;
    target = fn_80201814();
    effect = fn_80200C38(event);
    state = fn_801A74C0(effect);
    flags = fn_801A7570(effect);
    count = fn_801A7580(effect);

    if (target != NULL && fn_80201BC8(target) != NULL) {
        fn_80204844(fn_80201B9C(), 0x20);
        model = fn_8006D444();
        fn_800C43AC(&pos, target);
        if (fn_8006D344(model, 0xC0, 0) != 0) {
            fn_80088528(model, &pos);
        }
        hit = fn_800BE86C(owner, &pos, 2, &dist, lbl_8064F1C4);
        if (hit != 0 && !(state & 4)) {
            f32 d = dist;
            if (d < lbl_8064F110) {
                d = -d;
            }
            if (d < lbl_8064F1C8) {
                fn_800C3FE4(object, target, effect);
                if (flags & 4) {
                    fn_801A75A0(effect, count + 1);
                }
            }
        }
    }

    if (hit == 0) {
        fn_801A74D8(effect, 0x01000000);
        id = fn_801A77B0(effect);
        if (fn_801294DC(owner, id, 0x21, 1) == NULL) {
            state = flags & 0x90018;
            if (fn_8012915C(owner) == 0 || count != 0 ||
                (state != 0 && fn_800C4238(object, owner, target, effect) != 0)) {
                fn_801A75A0(effect, count + 1);
            }
            fn_800C3FE4(object, target, effect);
        } else if (!(state & 4)) {
            fn_800C3FE4(object, target, effect);
            if (flags & 4) {
                fn_801A75A0(effect, count + 1);
            }
        }
    }

    if (result != NULL) {
        *result = hit == 0;
    }
    return hit == 0;
}
