#pragma use_lmw_stmw on

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct RuntimeD6E4 {
    u8 pad00[0x50];
    void* values;
    u8 pad54[0x40];
    void* effect_source;
} RuntimeD6E4;

typedef struct ValuesD6E4 {
    u8 pad00[0x10];
    int first;
    int second;
} ValuesD6E4;

typedef struct EffectD6E4 {
    u8 pad00;
    u8 enabled;
    u8 alpha;
    s8 mode;
    u16 duration;
    u16 type;
    u8 pad08[0xE];
    u8 kind16;
    u8 kind17;
    u8 pad18[4];
    u32 value1C;
    u32 value20;
    u8 pad24[0x10];
    float scale;
    u8 pad38[4];
    u8 active;
    u8 size;
    u8 pad3E[0x52];
    void (*callback)(void);
    u8 pad94[0x14];
    u32 owner;
    u8 padAC[0x12];
    u8 flag;
    u8 padBF;
} EffectD6E4;

extern void* fn_80201B94();
extern int fn_80201C48(void*);
extern int fn_80201B54();
extern void *fn_80201814();
extern void* fn_8015C2FC(int);
extern void fn_80201E78(Vec3*, void*);
extern unsigned int fn_80178E94(Vec3*, Vec3*);
extern int fn_800DE3F8(void);
extern void fn_80140E58(void);
extern u8 fn_80203F60(void*, void*, Vec3*, Vec3*, int);
extern void *fn_801294DC(void *, int, int, int);
extern unsigned long long fn_8020123C();
extern void *fn_80201B8C();
extern int fn_800DEA28(void*);
extern void fn_80204810(void);
extern void fn_80128C28();
extern void *fn_80201BC8();
extern unsigned int fn_8011FA8C(void*, int, int);
extern void fn_8011FABC(void*, int, int);
extern int fn_801D3974(void*);
extern void fn_8011FF24(int*);
extern void fn_801AAE68(float, int, int, int, Vec3*, int, int, int, u16, int);
extern void* fn_80149E04(void);
extern void fn_80147E88(EffectD6E4*);
extern void fn_8014F4CC(EffectD6E4*, void*);
extern void fn_8019B13C(EffectD6E4*);
extern int fn_801D3A24(void*, int);
extern void* fn_80155DB4(void*);
extern void* fn_80148300(void*, EffectD6E4*, void*);
extern void fn_80149EB8(void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8012B344(void*);
extern float lbl_8064EC10;
extern float lbl_8064EC24;
extern const float lbl_8064EC28;
extern u32 lbl_8064D18C;

int fn_8008D6E4(void* object, void* resource)
{
    Vec3 spawn_position;
    Vec3 delta;
    Vec3 target_position;
    Vec3 object_position;
    EffectD6E4 effect;
    int pair[2];
    void* runtime_object;
    void* target;
    int object_id;
    int target_id;
    unsigned int distance;
    void* created;
    RuntimeD6E4* runtime;
    ValuesD6E4* values;
    void* collision;
    void* attachment;
    void* manager;
    void* spawned;

    runtime_object = fn_80201B94(object);
    object_id = fn_80201C48(runtime_object);
    target_id = fn_80201B54(object);
    target = fn_80201814(object_id);
    if (target != 0) {
        collision = fn_8015C2FC(2);
        fn_80201E78(&target_position, target);
        spawn_position = target_position;
        fn_80201E78(&object_position, object);
        delta = object_position;
        distance = fn_80178E94(&delta, &spawn_position);
        /* Refresh collision state immediately before probing the path. */
        if (object_id == fn_800DE3F8() ||
            (distance < 500 && (fn_80140E58(), fn_80203F60(resource, collision, &delta, &spawn_position, 0) == 0))) {
            created = fn_801294DC(resource, 139, 32, 6);
            if (created != 0) {
                fn_80201E78(&delta, object);
                delta.z += lbl_8064EC24;
                if ((u32)(fn_8020123C(125, target_id, object_id, 0) & 0xFFFFFFFF) == 1) {
                runtime = ((RuntimeD6E4*)fn_80201B8C(object));
                values = (ValuesD6E4*)runtime->values;
                if (fn_800DEA28(target)) {
                    values->second = object_id;
                    values->first = 0;
                } else {
                    values->first = object_id;
                    values->second = 0;
                }
                fn_80128C28(created, fn_80204810, (target_id << 8) | 6);
                attachment = fn_80201BC8(object);
                fn_8011FA8C(attachment, 0, 0x20000000);
                fn_8011FABC(attachment, 0, 1);
                pair[0] = pair[1] = fn_801D3974(runtime->effect_source);
                fn_8011FF24(pair);
                fn_801AAE68(lbl_8064EC28, 497, 100, 0, &delta, 2, 2, 0,
                            (u16)lbl_8064D18C, 0);
                spawned = fn_80149E04();
                if (spawned != 0) {
                    fn_80147E88(&effect);
                    fn_8014F4CC(&effect, spawned);
                    effect.owner = target_id;
                    ((int*)spawned)[2] = 0;
                    ((int*)spawned)[18] = 0;
                    fn_8019B13C(&effect);
                    effect.enabled = 6;
                    effect.type = 45;
                    effect.duration = fn_801D3A24(runtime->effect_source, 49);
                    effect.alpha = 160;
                    effect.mode = -2;
                    effect.value1C = 0;
                    effect.value20 = 0;
                    effect.kind16 = 5;
                    effect.kind17 = 160;
                    effect.scale = lbl_8064EC10;
                    manager = fn_80155DB4(object);
                    if (manager != 0) {
                        effect.flag = 0x80;
                        if (fn_80148300(manager, &effect, spawned) == 0)
                            fn_80149EB8(spawned);
                    } else {
                        fn_80149EB8(spawned);
                    }
                }
                fn_80201D2C(object, 59);
                fn_80201D14(object, 1);
                return 1;
                }
                fn_8012B344(resource);
            }
        }
    }
    return 0;
}
