typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Object80201EB8 Object80201EB8;

extern const Vec3 lbl_80239824;
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_80201EB8(Object80201EB8 *);
extern int fn_80201B54(int *);
extern int fn_80201B5C(int *);
extern unsigned short fn_8011F760(void *);
extern int fn_80204508(void *, void *);
extern int fn_800C17EC(void *, void *, Vec3 *, int, int);
extern u64 fn_8020123C(int, int, int, int);

int fn_800C193C(void *object)
{
    void *candidate = fn_80201B9C();
    void *inner = fn_80201BC8(object);
    Vec3 position;
    Vec3 inner_position;
    Vec3 fallback;
    Vec3 *source;
    int expected;
    int object_id;
    register int height;

    if (inner != 0) {
        fn_8011F114(&inner_position, inner);
        source = &inner_position;
    } else {
        fallback = lbl_80239824;
        source = &fallback;
    }
    position = *source;
    expected = fn_80201EB8(object);
    object_id = fn_80201B54(object);
    fn_8011F760(inner);
    /* ASM: mr reads the already zero-extended halfword return from r3;
     * MWCC otherwise adds a redundant clrlwi for the narrow return type. */
    asm { mr height, r3 }

    while (candidate != 0) {
        int candidate_id = fn_80201B54(candidate);
        int special = fn_80201B5C(candidate) == 0x40;

        if ((unsigned char)fn_80204508(object, candidate) != 0 &&
            (special || (unsigned char)fn_80204508(candidate, object) != 0) &&
            fn_800C17EC(candidate, object, &position, expected, height) != 0 &&
            (u32)(fn_8020123C(0x93, object_id, candidate_id, 0) & 0xFFFFFFFFULL) == 1) {
            return candidate_id;
        }
        candidate = fn_80201BC0(candidate);
    }
    return 0;
}
