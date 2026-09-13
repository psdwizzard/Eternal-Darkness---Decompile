typedef unsigned char u8;
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
    u8 pad00[0x8C];
    void *state;
    void *resource;
    u8 pad94[0xA];
    u8 special;
} OwnerData;

typedef struct OwnerState {
    u8 pad00[0x150];
    s16 count;
} OwnerState;

typedef struct Entry {
    s32 packed;
    s32 kind;
    s32 unused;
} Entry;

typedef enum Result {
    ResultFour = 4,
    ResultFive = 5,
    ResultSix = 6
} Result;

extern const float lbl_8064E5DC;
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void *fn_80201C48(void *);
extern int fn_80201B54();
extern void *fn_80201814();
extern void fn_8011F114();
extern s32 fn_80072354(void *);
extern s32 fn_80060840(void *, s32 *);
extern s32 fn_8006053C(void *, s32);
extern s32 fn_800601FC();
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void *fn_801294DC(void *, int, int, int);
#define fn_801294DC(a, b, c, d) fn_801294DC((void *)(a), (b), (c), (d))
extern void *fn_801A717C(void);
extern void fn_801A75A8(void *, s32);
extern void fn_801A75B8(void *, float);
extern void fn_801A7460(void *, s32);
extern void fn_801A74A0(void *, s32);
extern void fn_801A74A8(void *, void *);
extern void fn_801A74C8(void *, s32);
extern void fn_801A7550(void *, s32);
extern void fn_801A7558(void *, s32);
extern void fn_801A7598(void *, s32);
extern void fn_801A764C(void *, Vec3 *);
extern void fn_801A7560(void *, u32);
extern void fn_800CF6AC(void *, s32, OwnerData *, void *, s32, s32);
extern void fn_801292E0(void *, s32 *, Entry **);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8003B8A0(void);
extern void fn_800606BC(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);

s32 fn_80060904(void *owner, void *resource, void *target)
{
    OwnerData *owner_data;
    u32 owner_value;
    s32 special;
    Entry *entries;
    s32 list_count;
    Vec3 position;
    Vec3 source_position;
    void *created;
    s32 result;
    void *descriptor;
    void *target_value;
    s32 owner_id;
    u32 created_status;
    s32 resource_value;
    s32 i;
    s32 offset;
    s32 first;

    owner_data = fn_80201B8C(owner);
    owner_value = (u32)fn_80201B94(owner);
    fn_8011F114(&source_position, resource);
    position = source_position;
    special = 0;
    created_status = 0;
    target_value = fn_80201C48((void *)owner_value);
    owner_id = fn_80201B54(owner);

    if (((OwnerState *)owner_data->state)->count < 1) {
        ((OwnerState *)owner_data->state)->count = 0;
        fn_80072354(owner_data->resource);

        if (owner_data->special == 1) {
            result = fn_80060840(target, &special);
        } else {
            result = fn_8006053C(owner, 1);
        }

        if (special != 0) {
            result = -1;
            created_status = fn_800601FC(owner, fn_80201814(target_value), target);
            if (created_status == 0) {
                result = (fn_800FBFB0() & 1) ? ResultFour :
                         ((fn_800FBFB0() & 1) ? ResultFive : ResultSix);
            }
        }

        if (result != -1) {
            created = fn_801294DC(resource, result, 0, 6);
            if (created != 0) {
                descriptor = fn_801A717C();
                first = 1;
                if (result == 4) {
                    owner_value = 0;
                } else {
                    owner_value = result == 5 ? 1 : 2;
                }

                resource_value = fn_80072354(owner_data->resource);
                fn_801A75A8(descriptor, 0x10);
                fn_801A75B8(descriptor, lbl_8064E5DC);
                fn_801A7460(descriptor, result);
                fn_801A74A0(descriptor, owner_id);
                fn_801A74A8(descriptor, target_value);
                fn_801A74C8(descriptor, 1);
                fn_801A7550(descriptor, 0xC);
                fn_801A7558(descriptor, 7);
                fn_801A7598(descriptor, 500);
                fn_801A764C(descriptor, &position);
                {
                    u32 flags = 0x100A84;
                    if (result == 6) {
                        flags |= 0x400000;
                    }
                    fn_801A7560(descriptor, flags);
                }
                fn_800CF6AC(owner, resource_value, owner_data, descriptor, owner_value, result);

                fn_801292E0(resource, &list_count, &entries);
                i = 0;
                offset = 0;
                for (; i < list_count; offset += sizeof(Entry), i++) {
                    Entry *entry = (Entry *)((u8 *)entries + offset);
                    switch (entry->kind) {
                    case 1: {
                        s32 callback_arg = entry->packed >> 17;
                        if (first != 0) {
                            first = 0;
                            fn_801287C4(created, fn_8003B8A0, descriptor, callback_arg);
                        } else {
                            fn_801287C4(created, fn_800606BC, descriptor, callback_arg);
                        }
                        break;
                    }
                    }
                }
                fn_80128C28(created, fn_80204230, descriptor);
                fn_80128C44(created, fn_802042A4, descriptor);
                fn_80201D2C(owner, 6);
                fn_80201D14(owner, 1);
                created_status = 1;
            }
        }
    }
    return created_status;
}
