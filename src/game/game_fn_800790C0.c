#pragma use_lmw_stmw on
typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef unsigned char u8;

extern void* fn_80201B94();
extern void *fn_80201B8C();
extern int fn_80201B54();
extern void fn_8011F114();
extern int fn_800359A0(void *object, int kind);
extern int fn_80201C48(void *object);
extern void fn_800BDEE4(void *object, void *value);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

int fn_800790C0(void *object, void *actor, int unused, int flags, int mask)
{
    void *entry = fn_80201B94(object);
    u8 *state = fn_80201B8C(object);

    if ((flags & mask) == 0) {
        Vec3 position;
        fn_8011F114(&position, actor);
        fn_80201B54(object);
        if (fn_800359A0(object, 0) != 0) {
            if (fn_80201C48(entry) != 0) {
                fn_800BDEE4(object, *(void **)(state + 0x8C));
            }
            fn_80201D2C(object, 3);
            fn_80201D14(object, 1);
            return 1;
        }
    }
    return 0;
}
#pragma use_lmw_stmw off
