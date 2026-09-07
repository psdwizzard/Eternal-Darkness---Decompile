typedef unsigned char u8;
#pragma use_lmw_stmw on
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct RuntimeD9F4 {
    u8 pad00[0x9e];
    u8 flag9e;
    u8 type9f;
} RuntimeD9F4;

extern void* lbl_8064C4E4;
extern int lbl_8064D18C;
extern Vec3 lbl_8023963C;
extern void *fn_80201B9C();
extern void fn_8011F114();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern int fn_80201EB8();
extern unsigned int fn_80178E94(Vec3*, Vec3*);
extern unsigned long long fn_8020123C();
extern void* fn_80201BC0(void*);

int fn_8008D9F4(void* object, void* unused4, void* unused5, u8 flags)
{
    void* current;
    Vec3 base;
    Vec3 candidate;
    Vec3 initial;
    Vec3 fallback;
    unsigned int best_distance;
    int own_id;
    int best_id;

    current = fn_80201B9C(object);
    fn_8011F114(&initial, lbl_8064C4E4);
    base = initial;
    best_distance = 0;
    best_id = 0;
    own_id = fn_80201B54(object);
    while (current != 0) {
        RuntimeD9F4* runtime = ((RuntimeD9F4*)fn_80201B8C(current));
        void* attachment = fn_80201BC8(current);
        Vec3 constant;
        Vec3* selected;
        int candidate_id;
        unsigned int distance;
        int target_id;

        if (attachment != 0) {
            fn_8011F114(&fallback, attachment);
            selected = &fallback;
        } else {
            constant = lbl_8023963C;
            selected = &constant;
        }
        candidate = *selected;
        candidate_id = fn_80201EB8(current);
        target_id = fn_80201B54(current);
        distance = fn_80178E94(&base, &candidate) + 1;
        if (candidate_id == lbl_8064D18C && runtime != 0 &&
            (((flags & 1) && runtime->type9f == 10) ||
             ((flags & 2) && runtime->type9f == 24) ||
             ((flags & 2) && runtime->flag9e == 1)) &&
            attachment != 0 && distance > best_distance &&
            (unsigned int)(fn_8020123C(125, own_id, target_id, 0) & 0xFFFFFFFF) == 1) {
            best_distance = distance;
            best_id = target_id;
        }
        current = fn_80201BC0(current);
    }
    return best_id;
}
