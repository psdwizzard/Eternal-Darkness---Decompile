typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ObjectInfo {
    unsigned char pad_00[0x9F];
    unsigned char kind9F;
} ObjectInfo;

extern const Vec3 lbl_80238D70;
extern const Vec3 lbl_80238D7C;

extern void *fn_80201B9C();
extern void* fn_80201BC0(void*);
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern int fn_80201EB8();
extern int fn_80201B54();
extern void fn_8011F114();
extern u32 fn_80178E94(const Vec3*, const Vec3*);
extern unsigned long long fn_8020123C();
extern unsigned int rand(void);
#define rand() ((int)rand())

s32 fn_8003565C(register void* target, register s32* selected)
{
    register s32 candidate_kind;
    register s32 candidate_id;
    register s32 target_kind;
    register void* target_object;
    register void* iterator;
    register s32 target_id;
    register s32 count;
    register void* candidate_object;
    register ObjectInfo* info;
    Vec3 target_position;
    Vec3 candidate_position;
    Vec3 target_temporary;
    Vec3 target_fallback;
    Vec3 candidate_temporary;
    Vec3 candidate_fallback;
    Vec3* position;
    u32 message_result;

    iterator = fn_80201B9C();
    target_object = fn_80201BC8(target);
    if (target_object != 0) {
        fn_8011F114(&target_temporary, target_object);
        position = &target_temporary;
    } else {
        target_fallback = lbl_80238D70;
        position = &target_fallback;
    }
    target_position = *position;
    target_kind = fn_80201EB8(target);
    target_id = fn_80201B54(target);
    count = 0;

    while (iterator != 0) {
        info = fn_80201B8C(iterator);
        candidate_object = fn_80201BC8(iterator);
        if (candidate_object != 0) {
            fn_8011F114(&candidate_temporary, candidate_object);
            position = &candidate_temporary;
        } else {
            candidate_fallback = lbl_80238D7C;
            position = &candidate_fallback;
        }
        candidate_position = *position;

        candidate_kind = fn_80201EB8(iterator);
        candidate_id = fn_80201B54(iterator);
        if (target_kind == candidate_kind) {
            if (candidate_object != 0 && info != 0 && info->kind9F != 10 &&
                info->kind9F != 11 && info->kind9F != 16 &&
                info->kind9F != 30 && info->kind9F != 38 &&
                fn_80178E94(&target_position, &candidate_position) < 8500 &&
                target != iterator) {
                message_result = fn_8020123C(0x3B, target_id,
                                             candidate_id, 0) & 0xFFFFFFFFULL;
                if (message_result == 1 ||
                    ((message_result = fn_8020123C(
                          0xEF, target_id, candidate_id, 0) & 0xFFFFFFFFULL),
                     message_result == 1)) {
                    count++;
                    if (selected != 0 && *selected == 0) {
                        *selected = candidate_id;
                    } else if (selected != 0 && (rand() & 3) != 0) {
                        *selected = candidate_id;
                    }
                }
            }
        }
        iterator = fn_80201BC0(iterator);
    }
    return count;
}
