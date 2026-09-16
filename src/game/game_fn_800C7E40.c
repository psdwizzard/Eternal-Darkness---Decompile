typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Search {
    char query[8];
    unsigned int distance;
    unsigned char unknown[32];
} Search;

#pragma use_lmw_stmw on

extern void *fn_80201BC8();
extern int fn_8011FB4C(void *);
extern int lbl_8064D18C;
extern int fn_8011F598(void *, int, int, int, void *, int);
extern void* fn_80201B94();
extern int fn_80201C48(void *);
extern void *fn_80201814(int);
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS void *, void *
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern unsigned int fn_80178E94(void *, unsigned int *);
extern int fn_8011EB04(void *);
extern int fn_80201B54();
extern int fn_80201B44();
extern unsigned long long fn_8020123C();
extern Vec3 lbl_8023989C;
extern void *fn_801A717C(void);
extern unsigned char lbl_802FC5BC[];
extern float lbl_8064F22C;
extern float lbl_8064F21C;
extern float lbl_8064F224;
extern float lbl_8064F23C;
extern void fn_800CEA1C(int, int, void *, int, int, int, float, float, float,
                       void *);
extern void fn_8014D478(void *, void *, void *, int, int, void *, int);
extern void fn_801A74A0(void *, void *);
extern void fn_801A74A8(void *, void *);
extern void fn_801A7538(void *, int);
extern void fn_801A7518(void *, int);
extern void fn_801A764C(void *, void *);
extern void fn_801A7550(void *, int);
extern void fn_801A7228(void *);
extern void fn_80067180(void *);

void fn_800C7E40(void *object)
{
    void *runtime;
    int kind;
    unsigned int distance;
    int parent;
    unsigned int *distance_ptr;
    void *other;
    unsigned int limit;
    void *relation;
    void *sound;
    void *constant;
    unsigned long long result;
    unsigned char reference[12];
    Vec3 direction;
    Search search;

    runtime = fn_80201BC8(object);
    if (fn_8011FB4C(runtime) != lbl_8064D18C) {
        return;
    }
    if (fn_8011F598(runtime, 2, 15, -1, &search, 1) == -1) {
        return;
    }

    parent = fn_80201C48(fn_80201B94(object));
    other = fn_80201814(parent);
    if (other == 0) {
        return;
    }

    limit = 400;
    fn_80201E78(reference, other);
    distance_ptr = &search.distance;
    distance = fn_80178E94(reference, distance_ptr);
    kind = fn_8011EB04(runtime);
    if (kind == 0xFB) {
        limit = 100;
    }
    if (distance >= limit) {
        return;
    }

    relation = ((void *)fn_80201B54(object));
    if (kind != 0xFB) {
        if ((int)parent != (int)((void *)fn_80201B44(relation))) {
            fn_8020123C(0xD8, relation, relation, 0);
            return;
        }
        result = fn_8020123C(0x20, relation, parent, 0);
        if (result != 0) {
            fn_8020123C(0xD8, relation, relation, 0);
        } else {
            fn_8020123C(8, relation, parent, 0);
        }
        return;
    }

    direction = lbl_8023989C;
    if ((int)parent == (int)((void *)fn_80201B44(relation))) {
        sound = fn_801A717C();
        constant = lbl_802FC5BC + 0x18;
        fn_800CEA1C(0x17, 3, reference, 0, 5, 5, lbl_8064F22C,
                    lbl_8064F21C, lbl_8064F224, constant);
        fn_8014D478(runtime, distance_ptr, &direction, 5, 3,
                    constant, 3);
        fn_801A74A0(sound, relation);
        fn_801A74A8(sound, (void *)parent);
        fn_801A7538(sound, 1);
        fn_801A7518(sound, 0x3C);
        fn_801A764C(sound, reference);
        fn_801A7550(sound, 0xC);
        fn_8020123C(0x27, relation, parent, sound);
        fn_801A7228(sound);
    } else {
        fn_80067180(other);
        constant = lbl_802FC5BC + 0x18;
        fn_800CEA1C(0x17, 3, reference, 0, 5, 15, lbl_8064F23C,
                    lbl_8064F21C, lbl_8064F224, constant);
        fn_8014D478(runtime, distance_ptr, &direction, 10, 3,
                    constant, 3);
    }
}
