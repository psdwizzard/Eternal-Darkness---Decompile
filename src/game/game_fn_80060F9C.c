typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct OwnerData {
    u8 pad00[8];
    void *state;
} OwnerData;

typedef struct TargetState {
    u8 pad00[0x150];
    s16 count;
} TargetState;

extern const float lbl_8064E5DC;
extern const float lbl_8064E600;
extern const float lbl_8064E604;
extern const float lbl_8064E608;
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void fn_8011F114();
extern s32 fn_80066D04(void *, s32);
extern void fn_800359A0(void *, s32);
extern void fn_80201CD4(void *);
extern void *fn_80201C48(void *);
extern int fn_80201B54();
extern s32 fn_80060C28(void *, void *, void *);
extern s32 fn_800CA7D4(void *, void *, void *, void *, s32, s32);
extern s32 fn_80060904(void *, void *, void *);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012FE10(void *, s32, Vec3 *);
extern s32 fn_8012FF34(void *, Vec3 *, s32, s32);
extern void fn_801302BC(void *, s32);
extern void fn_802045AC(void *, Vec3 *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern float fn_8012B7D0(void *, Vec3 *);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern float fn_8011F6F8(void *);
extern s32 fn_8003E1F0(void *, Vec3 *, s32, float);
extern u8 fn_80204578(void *, Vec3 *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern s32 fn_8012AFC4(void *);
extern void fn_80129928(void *, Vec3 *);
extern void fn_8012976C(void *, s32, s32, Vec3 *, float);
extern s32 fn_800CCC78(void *, s32);
extern void fn_800360B0(void *, u16 *);
extern s32 fn_800601FC(void *, void *, void *);
extern s32 fn_800BE2CC(void *, void *, Vec3 *);
extern s32 fn_800BE260(void *, void *);
extern void fn_800BE390(void *, void *);
extern s32 fn_80128EAC(void *);
extern void fn_8012B344(void*);

s32 fn_80060F9C(void *owner, void *resource, void *probe, void *target,
                void *alternate, s32 mask, s32 flags)
{
    OwnerData *owner_data;
    s32 iterator;
    Vec3 resource_position;
    s32 relaxed;
    s32 result;
    void *value;
    Vec3 target_position;
    Vec3 delta;
    Vec3 alternate_position;
    Vec3 query_position;
    Vec3 retry_position;
    float angle;
    float facing;
    s32 distance;
    s32 ready;
    s32 created;
    u16 state;

    result = 0;
    owner_data = fn_80201B8C(owner);
    iterator = (s32)fn_80201B94(owner);
    fn_8011F114(&resource_position, resource);
    relaxed = 0;
    if (fn_80066D04(owner, 3) == 0 && fn_80066D04(owner, 2) == 0) {
        relaxed = 1;
    }
    if ((mask & flags) == 0) {
        fn_800359A0(owner, 0);
    }

    fn_80201CD4((void *)iterator);
    value = fn_80201C48((void *)iterator);
    if ((s32)fn_80201C48((void *)iterator) == 1 &&
        ((((u8 *)owner_data->state)[0x89] & 2) == 0)) {
        fn_80060C28((void *)fn_80201B54(owner), resource, owner_data);
        goto done;
    }
    iterator = (s32)value;

    if (fn_800CA7D4(probe, owner, target, resource, 30, 1) != 0) {
        result = fn_80060904(owner, resource, alternate);
        goto done;
    }

    if (iterator != 0 && (value = fn_80201814((void *)iterator)) != 0) {
        value = fn_80201BC8(value);
        if (value != 0 && ((TargetState *)target)->count == 0) {
            fn_8012FE10(value, 0, &target_position);
            if (*(s32 *)((u8 *)owner_data + 0x94) == 1 &&
                fn_8012FF34(resource, &target_position, 4, 4) != 0) {
                fn_801302BC(resource, 60);
            }

            fn_802045AC(owner, &delta);
            distance = fn_80178E94(&resource_position, &delta);
            query_position = delta;
            facing = fn_8012B7D0(resource, &query_position);
            fn_8017A12C(&angle, fn_8012B750(resource), facing);
            facing = fn_8011F6F8(resource);
            facing *= lbl_8064E600;

            if (relaxed == 0) {
                if (distance >= 400) {
                    if (distance >= 700) {
                        goto normal_path;
                    }
                    if (fn_8003E1F0(owner, &delta, 1, facing) == 0) {
                        goto normal_path;
                    }
                }

                retry_position = delta;
                facing = fn_8012B7D0(resource, &retry_position);
                fn_8017A12C(&angle, fn_8012B750(resource), facing);
                if (distance < 400 && fn_80204578(owner, &delta) != 0) {
                    float magnitude = angle;
                    if (magnitude < lbl_8064E5DC) {
                        magnitude = -magnitude;
                    }
                    if (magnitude <= lbl_8064E604) {
                        if (fn_80060904(owner, resource, alternate) == 0) {
                            fn_80201D2C(owner, 1);
                            fn_80201D14(owner, 1);
                        }
                        return 1;
                    }
                }

                if (fn_8012AFC4(resource) != 0) {
                    fn_80129928(resource, &delta);
                } else {
                    fn_8012976C(resource, 2, 0x21, &delta, lbl_8064E608);
                }
                goto done;
            }

normal_path:
            created = 0;
            ready = fn_800CCC78(owner, 1000);
            fn_800360B0(owner, &state);
            if (ready != 0 && relaxed == 0) {
                goto no_create;
            }
            if ((state & 0x80) != 0) {
                goto no_create;
            }
            created = fn_800601FC(owner, fn_80201814((void *)iterator), alternate);
            result = created;

no_create:
            if (created == 0 && relaxed == 0 &&
                fn_800BE2CC(owner, target, &alternate_position) != 0 &&
                fn_800BE260(owner, target) == 0) {
                if (fn_80178E94(&resource_position, &alternate_position) < 80) {
                    fn_800BE390(owner, target);
                } else if (fn_8012AFC4(resource) != 0) {
                    fn_80129928(resource, &alternate_position);
                } else {
                    fn_8012976C(resource, 2, 0x21, &alternate_position,
                                lbl_8064E608);
                }
                goto done;
            }

            if (fn_800BE260(owner, target) != 0) {
                result = 1;
                fn_80201D2C(owner, 1);
                fn_80201D14(owner, 1);
            } else if (created == 0 && relaxed != 0) {
                if (fn_8012AFC4(resource) == 0 &&
                    fn_80128EAC(resource) != 2) {
                    goto relaxed_complete;
                }
                fn_8012B344(resource);
relaxed_complete:
                result = 1;
                fn_80201D2C(owner, 1);
                fn_80201D14(owner, 1);
            } else if (created == 0) {
                result = 1;
                fn_80201D2C(owner, 1);
                fn_80201D14(owner, 1);
            }
            goto done;
        }
    }

    fn_80201D2C(owner, 1);
    fn_80201D14(owner, 1);
    result = 1;

done:
    return result;
}
