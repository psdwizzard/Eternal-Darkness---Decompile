typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed int s32;
typedef float f32;

typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct ActionData {
    u8 pad00[0x14];
    s32 target;
    s32 owner;
    u8 pad1C[0x144];
    u8 special;
} ActionData;
typedef struct OwnerData {
    u8 pad00[0x8C];
    ActionData *action;
    void *settings;
    u8 pad94[0xA];
    u8 mode;
} OwnerData;
typedef struct SettingEntry {
    u8 pad00[2];
    u8 amount;
    u8 flags;
    u8 pad04[4];
} SettingEntry;
typedef struct SettingTable {
    u8 pad00[0x28];
    SettingEntry entries[1];
} SettingTable;
typedef struct Entry { s32 flags, kind, value; } Entry;

extern const Vec3 lbl_80238DDC;
extern const f32 lbl_8064E294, lbl_8064E2A0, lbl_8064E2A4;
extern const f32 lbl_8064E2A8, lbl_8064E2AC, lbl_8064E2B0, lbl_8064E2B4;
extern s32 fn_8003B8A0(void *, void *);
extern u32 fn_8003D30C(void *, void *);
extern s32 fn_80204230(s32, s32), fn_802042A4(s32, s32);
extern s32 fn_80204810(void *, s32);
extern s32 fn_8003C934(void *, s32);
extern f32 fn_8003CC1C(Vec3 *);
extern s32 fn_8003CC48(void *, OwnerData *, s32, short);
extern s32 fn_8006D3E4(s32, s32);
extern SettingTable *fn_80072354(void *);
extern void fn_800CF6AC(void *, SettingTable *, OwnerData *, void *, s32, s32);
extern s32 fn_800FBFB0(void), fn_8011EB04(void *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_801287C4(void *, void *, u32, u32);
extern void fn_80128C28(void *, u32, u32);
extern void fn_80128C44(void *, u32, u32);
extern u8 fn_80128EE4(void *);
extern void fn_801292E0(void *, s32 *, Entry **);
extern void *fn_801294DC(void *, s32, s32, s32);
extern void fn_80129BA4(void *, f32, f32);
extern void fn_8012B344(void *);
extern f32 fn_8012B750(void *), fn_8012B7D0(void *, Vec3 *);
extern void fn_8012E114(void *, s32, Vec3 *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern void fn_8017A12C(f32 *, f32, f32);
extern void *fn_801A717C(void);
extern u16 fn_801A7434(void *), fn_801A7578(void *);
extern void fn_801A7460(void *, s32), fn_801A74A0(void *, s32), fn_801A74A8(void *, s32);
extern void fn_801A74C8(void *, s32), fn_801A7550(void *, s32), fn_801A7558(void *, s32);
extern u32 fn_801A7560(void *, u32);
extern void fn_801A7598(void *, u16), fn_801A764C(void *, Vec3 *);
extern void *fn_80200C38(void *);
extern u64 fn_8020123C(s32, s32, s32, s32);
extern void *fn_80201814(s32);
extern s32 fn_80201B54(void *), fn_80201B5C(void *);
extern OwnerData *fn_80201B8C(void *);
extern void *fn_80201B94(void *), *fn_80201BC8(void *);
extern void *fn_80201C48(void *);
extern void fn_80201D14(void *, s32), fn_80201D1C(void *, s32);
extern void fn_80201D2C(void *, s32), fn_80201D34(void *, s32);
extern void fn_80204508(void *, void *);

s32 fn_8003CD0C(void *owner, void *object, void *event)
{
    ActionData *action;
    OwnerData *owner_data;
    void *effect, *created, *target_object, *target, *owner_link;
    SettingTable *settings;
    Vec3 target_position, object_position, default_position;
    Vec3 start_position, direction_position, second_position;
    f32 angle, facing, difference;
    Entry *entries;
    s32 count;
    f32 second_angle;
    s32 is_normal, pending, kind, owner_id, target_id;
    s32 index, offset, amount_kind;
    u32 strength;
    s32 alternative;

    owner_data = fn_80201B8C(owner);
    owner_link = fn_80201B94(owner);
    fn_8011F114(&start_position, object);
    object_position = start_position;
    fn_80128EE4(object);
    target_id = (s32)fn_80201C48(owner_link);
    owner_id = fn_80201B54(owner);
    action = owner_data->action;
    target_object = fn_80201814(target_id);
    if (target_object != 0) target = fn_80201BC8(target_object);
    else target = 0;
    if (target != 0) fn_8011F114(&target_position, target);

    if (owner_data->mode == 1) {
        switch (fn_801A7434(fn_80200C38(event))) {
        case 16: kind = 4; break;
        case 8: kind = 5; break;
        case 2: kind = 6; break;
        default:
            {
                s32 flags = fn_800FBFB0();
                s32 choice = 5;
                if (flags & 1) choice = 4;
                kind = choice;
            }
            break;
        }
    } else kind = fn_8003C934(owner, 1);

    if (kind == 6 && target_object != 0) {
        u32 distance = fn_80178E94(&object_position, &target_position);
        s32 nearby = 0;
        if (distance <= 123 && distance >= 100) nearby = 1;
        facing = fn_8012B750(object);
        angle = lbl_8064E2A0;
        if (nearby != 0) {
            direction_position = target_position;
            fn_8017A12C(&angle, facing, fn_8012B7D0(object, &direction_position));
        }
        if (nearby != 0) {
            difference = angle;
            if (difference < lbl_8064E294) difference = -difference;
            if (difference < lbl_8064E2A4) {
                fn_80204508(target_object, owner);
                if (fn_8011EB04(object) == 9 || fn_8011EB04(object) == 70) {
                    alternative = 1;
                    is_normal = 94;
                } else {
                    alternative = 0;
                    is_normal = 88;
                }
                created = fn_801294DC(object, is_normal, 32, 6);
                if (created != 0) {
                    if ((u32)(fn_8020123C(32, owner_id, target_id, 0) & 0xFFFFFFFFULL) != 0) {
                        fn_80128C28(created, (u32)fn_80204810, (owner_id << 8) | 0x21);
                        action->target = target_id;
                        action->owner = fn_80201B5C(owner);
                        action->special = alternative;
                        fn_80201D34(owner, 18);
                        fn_80201D1C(owner, 1);
                        return 1;
                    }
                    fn_8012B344(object);
                }
            }
        }
        kind = fn_8003C934(owner, 0);
    } else if (kind == 6) kind = 4;

    if (kind == -1) goto fail;
    created = fn_801294DC(object, kind, target != 0 ? 0x100 : 0, 6);
    if (created == 0) goto fail;
    effect = fn_801A717C();
    default_position = lbl_80238DDC;
    pending = 1;
    if (target != 0) {
        f32 magnitude;
        second_position = target_position;
        facing = fn_8012B7D0(object, &second_position);
        fn_8017A12C(&second_angle, fn_8012B750(object), facing);
        if (second_angle < lbl_8064E294) magnitude = -second_angle;
        else magnitude = second_angle;
        if (magnitude > lbl_8064E2A8) {
            f32 narrow = second_angle;
            if (narrow < lbl_8064E294) narrow = -narrow;
            if (narrow < lbl_8064E2AC) fn_80129BA4(created, facing, lbl_8064E2B0);
        }
    }

    is_normal = ((u32)((4 - kind) | (kind - 4))) >> 31;
    settings = fn_80072354(owner_data->settings);
    fn_801A7460(effect, kind);
    fn_801A74A0(effect, owner_id);
    fn_801A74A8(effect, target_id);
    if (fn_8006D3E4(0x50000, 0) == 0) fn_801A74C8(effect, 1);
    fn_801A7560(effect, 0x100A84);
    {
        u8 input = settings->entries[is_normal].amount;
        register OwnerData *source_owner_data = owner_data;
        register OwnerData *call_owner_data;
        amount_kind = 2;
        /* ASM: mr places the object argument before the mode branch; C delays this move until the call. */
        asm { mr call_owner_data, source_owner_data }
        if (kind == 4) amount_kind = 3;
        fn_8003CC48(owner, call_owner_data, amount_kind, input);
    }
    fn_801A7550(effect, 12);
    fn_801A7558(effect, 7);
    fn_801A764C(effect, &object_position);
    fn_800CF6AC(owner, settings, owner_data, effect, is_normal, kind);
    strength = (u16)fn_801A7578(effect);
    fn_8012E114(object, 15, &default_position);
    {
        f32 multiplier = fn_8003CC1C(&default_position);
        multiplier += lbl_8064E2B4;
        fn_801A7598(effect, (s32)((f32)strength * multiplier));
    }
    fn_801292E0(object, &count, &entries);
    for (index = 0, offset = 0; index < count; index++, offset += 12) {
        Entry *entry = (Entry *)((u8 *)entries + offset);
        switch (entry->kind) {
        case 1: {
            s32 callback_kind = entry->flags >> 17;
            if (pending != 0) {
                pending = 0;
                fn_801287C4(created, fn_8003B8A0, (u32)effect, callback_kind);
            } else fn_801287C4(created, fn_8003D30C, (u32)effect, callback_kind);
            break;
        }
        default:
            break;
        }
    }
    fn_80128C28(created, (u32)fn_80204230, (u32)effect);
    fn_80128C44(created, (u32)fn_802042A4, (u32)effect);
    fn_80201D2C(owner, 6);
    fn_80201D14(owner, 1);
    return 1;
fail:
    return 0;
}
