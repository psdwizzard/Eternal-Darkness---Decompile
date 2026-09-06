typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void *fn_80201C48(void *);
extern void *fn_80201814();
extern void fn_8012FE10(void *, int, Vec3 *);
extern int fn_8012FF34(void *, Vec3 *, int, int);
extern void fn_801302BC(void *, int);
extern void fn_8011FE64(void *, int);

void fn_80077704(void *object)
{
    void *target;
    void *runtime;
    u8 *state;
    void *source;
    Vec3 position;

    target = fn_80201BC8(object);
    runtime = fn_80201B8C(object);
    source = fn_80201B94(object);
    state = *(u8 **)((u8 *)runtime + 0x44);
    source = fn_80201C48(source);
    source = fn_80201814(source);
    source = fn_80201BC8(source);
    fn_8012FE10(source, 0, &position);
    if (fn_8012FF34(target, &position, 4, 4) != 0) {
        fn_801302BC(target, state[0x1BF] + 0x2D);
    }
    fn_8011FE64(target, 0);
}
