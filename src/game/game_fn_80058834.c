typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;
typedef struct Vec3 { float x, y, z; } Vec3;

#pragma use_lmw_stmw on

extern char lbl_80243A40[], lbl_8064B4E4, lbl_80331748[];
extern const Vec3 lbl_80238FDC;
extern volatile float lbl_8064E4EC;
extern float lbl_8064E504, lbl_8064E508, lbl_8064E50C;
extern float lbl_8064E510, lbl_8064E514, lbl_8064E518, lbl_8064E51C;
extern float lbl_8064E520, lbl_8064E524;
extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void fn_8011F114();
extern void fn_80130434(void *, s32);
extern void fn_801301B0(void *, u32, u32);
extern void *fn_80201B9C();
extern void* fn_80204844(void *, s32);
extern void *fn_8006D444(void);
extern s32 fn_8006D344(void *, s32, s32);
extern s32 fn_80088528(void *, Vec3 *);
extern s32 fn_801A7490(void *);
extern void *fn_80201814();
extern u32 fn_801A74C0(void *), fn_801A7770(void *);
extern void fn_80036B7C(void *, u32, Vec3 *);
extern void fn_8011E174(s32, s32);
extern float fn_8012B7D0(void *, Vec3 *), fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern void fn_80211A6C();
extern float fn_80211B08(Vec3 *);
extern u8 fn_80204434(void *, Vec3 *, s32, float);
extern void fn_8012B6FC(void *, Vec3 *, Vec3 *);
extern void *fn_8004914C(void *);
extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern void fn_80211A90(Vec3 *, Vec3 *, float);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern s32 fn_801A77B0(void *);
extern void *fn_8012976C(void *, s32, u32, Vec3 *, float);
extern void fn_80128B8C(void *, Vec3 *), fn_80129BA4(void *, float, float);
extern void *fn_80129A00(void *, s32, s32, float, float);
extern void fn_80128C28(), fn_80128C44(void *, void *, u32);
extern void fn_801A74D8(void *, u32);
extern void *fn_801294DC(void *, int, int, int);
#define fn_801294DC(a, b, c, d) fn_801294DC((void *)(a), (b), (c), (d))
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern s32 fn_80035FB8(void *, char *, char *, char *, char *, char *);
extern int fn_80200C38();
extern s32 fn_80070A6C(s32);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a, b, c, d, e) fn_8020104C((a), (void *)(b), (void *)(c), (int)(d), (e))
extern void fn_800C39D0(void *), fn_800C2474(void *, s32);
extern s32 fn_802006D4(void *, void *, s32, s32, s32);
extern u64 fn_802011D4(void *);
extern s32 fn_801261F4(void *);
extern void fn_8012B344(void*);
extern void fn_80204810(void);

s32 fn_80058834(void *context, void *event, u32 *result)
{
    char *strings = lbl_80243A40;
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);
    s32 value = (s32)fn_80201B54(context);
    void **state_ref = fn_80201B8C(context);
    Vec3 original;
    Vec3 position;
    Vec3 direction;
    Vec3 scaled;
    Vec3 offset;
    Vec3 basis;
    Vec3 current_position;
    Vec3 temporary;

    fn_8011F114(&current_position, object);
    original = current_position;
    if (kind == 1) {
        u32 linked;
        void **state;
        s32 handled = 0;
        s32 adjusted = 0;
        void *probe;
        s32 special;
        s32 moved = 0;
        void *resolved;
        float facing;
        float distance;
        float angle;

        special = 0;
        fn_80130434(object, 1);
        fn_801301B0(object, 0, 0x20);
        state = (void **)*state_ref;
        linked = (u32)*state;
        fn_80204844(fn_80201B9C(), 0x20);
        probe = fn_8006D444();
        if (fn_8006D344(probe, 0xC0, 0) != 0 && fn_80088528(probe, &position) != 0) special = 1;
        resolved = fn_80201814(fn_801A7490((void *)linked));
        if (special != 0 || resolved != 0) {
            if (special == 0) {
                void *current = fn_80201BC8();
                if ((fn_801A74C0((void *)linked) & 0x20) != 0) {
                    fn_80036B7C(current, fn_801A7770((void *)linked), &position);
                    fn_8011E174(8, 1);
                } else fn_8011F114(&position, current);
            }
            temporary = position;
            facing = fn_8012B7D0(object, &temporary);
            distance = fn_8012B750(object);
            fn_8017A12C(&angle, distance, facing);
            if ((fn_801A74C0((void *)linked) & 0x20) != 0) {
                float separation;
                s32 blocked;
                fn_80211A6C(&original, &position, &direction);
                separation = fn_80211B08(&direction);
                blocked = fn_80204434(object, &position, 0, lbl_8064E508) == 0;
                if (separation <= lbl_8064E50C || blocked != 0) {
                    basis = lbl_80238FDC;
                    fn_8012B6FC(object, &basis, &basis);
                    direction = basis;
                    facing = distance;
                    angle = lbl_8064E4EC;
                    if (blocked != 0) separation = -separation;
                }
                distance = lbl_8064E510;
                if (fn_8011EB04(fn_8004914C((void *)linked)) == 120 &&
                    fn_8011EB04(object) == 73) distance = lbl_8064E514;
                if (separation < distance) {
                    fn_80211AAC(&direction, &direction);
                    fn_80211A90(&direction, &scaled, lbl_8064E518);
                    fn_80211A90(&direction, &direction, distance - separation);
                    fn_80211A48(&original, &direction, &offset);
                    adjusted = 1;
                }
            }
            if ((angle < lbl_8064E4EC ? -angle : angle) > lbl_8064E51C) moved = 1;
            if (moved != 0 || adjusted != 0) {
                s32 mode;
                handled = 1;
                if ((angle < lbl_8064E4EC ? -angle : angle) > lbl_8064E520 || adjusted != 0) mode = 2;
                else mode = fn_801A77B0((void *)linked);
                if (adjusted != 0) {
                    resolved = fn_8012976C(object, mode, 0x8023, &offset, lbl_8064E524);
                    if (resolved != 0) {
                        fn_80128B8C(object, &scaled);
                        fn_80129BA4(resolved, facing, lbl_8064E524);
                    }
                } else resolved = fn_80129A00(object, mode, 0x25, facing, lbl_8064E524);
                if (resolved != 0) {
                    u32 upper = (u32)value << 8;
                    fn_80128C28(resolved, fn_80204810, upper | 6);
                    fn_80128C44(resolved, fn_80204810, upper | 7);
                } else {
                    fn_80201D2C(context, 1);
                    fn_80201D14(context, 1);
                }
            }
        }
        if (handled == 0) {
            fn_801A74D8((void *)linked, 0x01000000);
            fn_801294DC(object, fn_801A77B0((void *)linked), 0x21, 1);
            fn_80201D2C(context, 0x58);
            fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 7) {
        if (fn_80035FB8(context, strings + 0xA0, strings + 0x164, strings + 0xCC,
                        &lbl_8064B4E4, strings + 0xD8) == 0) {
            fn_80201D2C(context, 1); fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 6) {
        void *linked = *(void **)*state_ref;
        fn_801294DC(object, fn_801A77B0(linked), 0x21, 1);
        fn_801A74D8(linked, 0x01000000);
        fn_80201D2C(context, 0x58); fn_80201D14(context, 1);
        return 1;
    }
    if (kind == 40) {
        if (fn_80070A6C(0x200) == 0) {
            void *linked = (void *)fn_80200C38(event);
            if ((fn_801A74C0(linked) & 0x400) != 0)
                fn_8020104C(40, (void *)value, (void *)value, (int)linked, lbl_8064E504);
        }
        return 1;
    }
    if (kind == 61) {
        fn_800C39D0(context); **(void ***)state_ref = 0; fn_800C2474(object, 1);
        fn_80201D2C(context, 1); fn_80201D14(context, 1); return 1;
    }
    if (kind == 60) {
        fn_802006D4((void *)value, (void *)value, -1, 40, 0); fn_800C39D0(context);
        if (result != 0) *result = fn_802011D4(event) & 0xFFFFFFFFULL;
        fn_80201D2C(context, 1); fn_80201D14(context, 1); return 1;
    }
    if (kind == 175) {
        if (*(void **)(lbl_80331748 + 0xAC) != 0) {
            **(void ***)state_ref = 0; fn_800C39D0(context); fn_801261F4(object); fn_8012B344(object);
            if (result != 0) *result = 1;
            fn_80201D2C(context, 0x40); fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 2) { fn_8011E174(8, 0); fn_801301B0(object, 0x20, 0); return 1; }
    if (kind == 52) return 1;
    if (kind == 69) return 1;
    if (kind == 41) return 1;
    if (kind == 42) return 1;
    if (kind == 45) return 1;
    if (kind == 44) return 1;
    if (kind == 46) return 1;
    if (kind == 177) return 1;
    if (kind == 155) return 1;
    if (kind == 178) return 1;
    if (kind == 204) return 1;
    if (kind == 202) return 1;
    if (kind == 147) return 1;
    return (u8)(kind == 31);
}
