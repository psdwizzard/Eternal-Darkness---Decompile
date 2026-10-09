typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef float f32;
#define NULL 0

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct ObjectContext {
    u8 pad0[0x8C];
    void *unk8C;
} ObjectContext;

extern void **fn_800BC100(int, Vec3 *, int, int, int *, int *, int);
extern void fn_800BCCC4(void *, Vec3 *);
extern void fn_800BD194(void *, void *);
extern void fn_800BD2DC(void *, void *);
extern void fn_800BDEE4(void *, void *);
extern void fn_800BE010(void *, void *);
extern int fn_800BE0F4(void *, void *);
extern void fn_800BE158(void *, void *);
extern int fn_800BE1F4(void *, void *);
extern int fn_800BE2CC(void *, void *, Vec3 *);
extern void fn_800BE390(void *, void *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_8012976C(void *, int, int, Vec3 *, f32);
extern void fn_80129928(void *, Vec3 *);
extern int fn_8012AFC4(void *);
extern void fn_8012B324(void *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern int fn_801E8328();
extern int fn_80200C10(void *);
extern int fn_80201B54(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern u32 fn_80201CD4(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201E60(void *, u32);
extern void fn_80201F44(void *, Vec3);

extern s32 lbl_8064CA84;
extern f32 lbl_8064F108;

int fn_800BE408(void *object, int state, void *event) {
    Vec3 position;
    Vec3 fetched;
    Vec3 target;
    int range;
    int lifetime;
    void *info;
    void *relation;
    int kind;
    ObjectContext *context;
    void **spawned;
    void *runtime;

    kind = fn_80200C10(event);
    runtime = fn_80201BC8(object);
    context = fn_80201B8C(object);
    relation = fn_80201B94(object);
    info = context->unk8C;
    fn_80201B54(object);
    fn_8011F114(&position, runtime);

    if (state == 0) {
        if (kind == 1) {
            fn_800BD194(object, info);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x39) {
            fn_8012B324(runtime);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        } else if (kind == 0x3D) {
            fn_800BD2DC(object, info);
            return 1;
        } else if (kind == 0x3E) {
            fn_800BD194(object, info);
            return 1;
        }
    } else if (state == 1) {
        if (kind == 3) {
            if (fn_800BE1F4(object, info) == 0) {
                range = 500;
                lifetime = 10000;
                spawned = fn_800BC100(0, &position, 0, 8, &range, &lifetime, 0);
                if (spawned != NULL && *spawned != 0) {
                    fn_80201E60(relation, fn_80201CD4(relation) | 0x20);
                    fn_800BCCC4(*spawned, &fetched);
                    fn_80201F44(object, fetched);
                    fn_800BDEE4(object, info);
                }
            } else {
                fn_800BE010(object, info);
                if (fn_800BE0F4(object, info) != 0) {
                    if (lbl_8064CA84 != 0) {
                        /* ASM: nop -- stripped assertion in the empty branch; C cannot emit it */
                        asm { nop }
                    }
                    lbl_8064CA84++;
                    fn_80201D2C(object, 0x3E);
                    fn_80201D14(object, 1);
                }
            }
            return 1;
        }
    } else if (state == 0x3E) {
        if (kind == 3) {
            if (fn_800BE2CC(object, info, &target) != 0) {
                if (fn_80178E94(&position, &target) < 0x50) {
                    fn_800BE390(object, info);
                } else if (fn_8012AFC4(runtime) != 0) {
                    fn_80129928(runtime, &target);
                } else {
                    fn_8012976C(runtime, 3, 0x21, &target, lbl_8064F108);
                }
            } else {
                fn_800BE158(object, info);
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
