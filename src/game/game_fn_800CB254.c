typedef unsigned int u32;
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;
typedef struct Object80201EB8 Object80201EB8;
typedef struct GlobalMode {
    char pad[8];
    int mode;
} GlobalMode;

extern void *fn_80201B9C(void);
extern int fn_80201ADC(void);
extern void *fn_80201BC8(void *);
extern void *fn_80201BC0(void *);
extern int fn_80201EB8(Object80201EB8 *);
extern int fn_80201B4C(int *);
extern int fn_80201B64(int *);
extern int fn_80201B5C(int *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern u32 fn_80178E94(const float *, const float *);
extern const Vec3 lbl_802398C8;
extern GlobalMode lbl_803003C8;

int fn_800CB254(void *source, u32 range, Vec3 *source_position, int owner, int restrict_kind)
{
    void *candidate = fn_80201B9C();
    int first = fn_80201ADC();
    int count = 0;
    Vec3 position;

    {
        void *source_transform;
        if (source != 0 && source_position != 0) {
            position.x = source_position->x;
            position.y = source_position->y;
            position.z = source_position->z;
        } else if (source != 0 &&
                   (source_transform = fn_80201BC8(source)) != 0) {
            fn_8011F114(&position, (Vec3 *)source_transform);
        } else {
            position.x = source_position->x;
            position.y = source_position->y;
            position.z = source_position->z;
        }
    }

    while (candidate != 0) {
        Vec3 candidate_position;
        Vec3 transformed;
        Vec3 fallback;
        Vec3 *chosen;
        void *transform = fn_80201BC8(candidate);
        int candidate_owner;
        int object_kind;

        if (transform != 0) {
            fn_8011F114(&transformed, (Vec3 *)transform);
            chosen = &transformed;
        } else {
            fallback = lbl_802398C8;
            chosen = &fallback;
        }
        candidate_position = *chosen;
        candidate_owner = fn_80201EB8((Object80201EB8 *)candidate);
        object_kind = fn_80201B4C((int *)candidate);
        if (owner == candidate_owner &&
            fn_80178E94(&position.x, &candidate_position.x) < range &&
            source != candidate &&
            (object_kind == 1 || object_kind == 0)) {
            int subtype = fn_80201B64((int *)candidate);
            int type = fn_80201B5C((int *)candidate);
            if (restrict_kind != 0 && (u32)candidate == (u32)first && lbl_803003C8.mode == 3) {
                count++;
            } else if (restrict_kind == 0 ||
                       (type != 0x40 && type != 0x45 && type != 0x15 && (u32)(subtype - 8) > 1)) {
                count++;
            }
        }
        candidate = fn_80201BC0(candidate);
    }
    return count;
}
