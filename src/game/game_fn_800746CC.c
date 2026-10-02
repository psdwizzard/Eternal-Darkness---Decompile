typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State {
    u8 pad_00[0x19C];
    Vec3 position;
    u8 pad_1A8[0x1A];
    u8 active;
} State;

typedef struct Object Object;
typedef struct Link Link;

typedef struct Owner {
    u8 pad_00[0x44];
    State *state;
} Owner;

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

int fn_800746CC(void *arg0, void *arg1)
{
    Object *object;
    Link *link;
    void *first;
    void *second;
    State *state;
    Vec3 position;
    void *position_object;

    object = arg0;
    link = arg1;
    if (fn_80128EAC(object) == 7) {
        first = fn_801A7498(link);
        second = fn_801A7490(link);
        state = ((Owner *)fn_80201B8C(fn_80201814(first)))->state;
        position_object = fn_80201BC8(fn_80201814(second));
        fn_8011F114(&position, position_object);
        if (fn_80178E94(&state->position, &position) > 200) {
            fn_80128BE4(object);
            state->active = 1;
            fn_8020123C(0x74, first, second, 0);
            fn_8020123C(0x74, first, first, 0);
        } else {
            fn_8011FA8C(object, 0xC0, 0);
        }
    }
    return 1;
}
