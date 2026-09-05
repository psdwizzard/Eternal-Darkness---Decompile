typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef float f32;

typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

typedef struct Vec3s {
    s16 x, y, z;
} Vec3s;

typedef struct Pair {
    void* first;
    void* second;
} Pair;

typedef struct Locals {
    Vec3s packed;
    u16 pad;
    Vec3f position;
    Pair pair;
    u32 conversion_pad[2];
} Locals;

extern void* fn_80201AE4(void*);
extern void* fn_80201814(void*);
extern void* fn_80201C24(void*);
extern void* fn_80157888(void*);
extern u32 fn_80157894(void*);
extern void fn_80201E78(Vec3f*, void*);
extern void fn_80205470(u32, void*, Vec3s*, u32, f32);
extern void* fn_80158598(void*, u32);
extern void* fn_80158550(void*, void*);
extern int fn_80158390(void*, void*, u32);
extern void fn_800CC140(void*, void*, u32, void*, u32);
extern void fn_8011E174(u32, u32);
extern void fn_801D0794(u32, u32, void*, Pair*, void*, u32, void*, u32);
extern void fn_801D0C94(void);
extern void fn_801D0C9C(void);
extern const f32 lbl_80651068;
extern const f32 lbl_8065106C;
extern u32 lbl_8064D54C;

void fn_801CFE3C(void* source, u32 flags_a, u32 flags_b, void* target)
{
    Locals local;
    void* source_object;
    u32 dispatch_flags;
    void* target_data;
    void* saved_source;
    void* source_model;
    void* source_position;
    void* source_data;

    saved_source = source;
    target_data = target;
    dispatch_flags = (flags_a | 0x300) | flags_b;
    source_object = fn_80201AE4(source);
    source_model = fn_80201814(source_object);
    source_position = fn_80201814(source);

    if (source_model != 0 && source_position != 0 && (int)target_data != 0) {
        void* target_object = fn_80201814(target_data);
        source_data = fn_80201C24(target_object);
        {
            void* target_model = fn_80157888(source_data);
            if (fn_80157894(source_data) & 1) {
                fn_80201E78(&local.position, (void*)((u32)source_position | 0));
                local.packed.x = (s16)(int)local.position.x;
                local.packed.y = (s16)(int)local.position.y;
                local.packed.z = (s16)(int)(lbl_80651068 + local.position.z);
                fn_80205470(0, target_data, &local.packed, 0x48, lbl_8065106C);
                local.pair.first = target_data;
            } else if ((u32)target_model & 1) {
                void* list = fn_80158598(source_object, 0);
                if (fn_80158550(list, target_data) == 0) {
                    int index = fn_80158390(list, source_data, 1);
                    if (index >= 0) {
                        void** table = *(void***)source_data;
                        fn_800CC140(source_object, target_data, 0,
                                    ((void**)*table)[index], 0);
                    }
                }
                local.pair.first = target_data;
            }
        }
        local.pair.second = source_object;
        fn_8011E174(0x800, 1);
        lbl_8064D54C = 1;
        fn_801D0794(dispatch_flags, 1, saved_source, &local.pair, fn_801D0C9C, 0,
                    fn_801D0C94, 0);
    }
}
