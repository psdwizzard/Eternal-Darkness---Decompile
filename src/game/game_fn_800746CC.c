typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State {
    u8 pad_00[0x1C2];
    u8 active;
} State;

extern int fn_80128EAC(void *);
extern void *fn_801A7498(void *);
extern void *fn_801A7490(void *);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern void fn_8011F114();
extern unsigned int fn_80178E94(const Vec3 *, const Vec3 *);
extern void fn_80128BE4(void *);
extern unsigned long long fn_8020123C();
extern unsigned int fn_8011FA8C(void *, int, int);

/* NonMatching: behavior-complete paired-object distance event handler. The
 * remaining differences are callee-saved register allocation and prologue
 * scheduling. */
int fn_800746CC(void *object, void *link)
{
    register State *state;
    register void *second;
    register void *first;
    register void *object_r;
    register void *position_object;
    Vec3 position;

    object_r = object;
    first = link;
    if (fn_80128EAC(object_r) == 7) {
        first = fn_801A7498(first);
        second = fn_801A7490(link);
        state = *(State **)((u8 *)fn_80201B8C(fn_80201814(first)) + 0x44);
        position_object = fn_80201BC8(fn_80201814(second));
        fn_8011F114(&position, position_object);
        if (fn_80178E94((Vec3 *)((u8 *)state + 0x19C), &position) > 200) {
            fn_80128BE4(object_r);
            state->active = 1;
            fn_8020123C(0x74, first, second, 0);
            fn_8020123C(0x74, first, first, 0);
        } else {
            fn_8011FA8C(object_r, 0xC0, 0);
        }
    }
    return 1;
}
