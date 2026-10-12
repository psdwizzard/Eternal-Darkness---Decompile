/* Update sanity levels and the events used by insanity effects.
 * Remaining code differences are the compiler's GPR save/restore helpers
 * and its pooled signed-integer conversion constant.
 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ModeState {
    u8 active;
    u8 pad01[3];
    u8 pending;
    u8 pad05;
    u8 timer;
    u8 pad07[3];
    u16 state;
} ModeState;

typedef struct Owner {
    u8 pad00[0x15];
    u8 mode;
    u8 pad16[0x26];
    float sanityRatio;
    u8 pad40[0x84];
    ModeState *modeState;
} Owner;

typedef struct ObjectData {
    u8 pad00[0x44];
    s32 id;
} ObjectData;

typedef struct ObjectInfo {
    u8 pad00[0x8C];
    ObjectData *data;
    u8 pad90[0xE];
    u8 flag9E;
    u8 flag9F;
} ObjectInfo;

typedef struct ShortVec3 {
    s16 x, y, z;
} ShortVec3;

extern char lbl_80243EE8[];
extern const Vec3 lbl_802390C8;
extern s32 lbl_803003C8[];
extern s32 lbl_8064B538;
extern s32 lbl_8064B824;
extern u32 *lbl_8064C4E0;
extern void *lbl_8064C4E4;
extern s32 lbl_8064C8B8;
extern s32 lbl_8064C8BC;
extern s32 lbl_8064CBC0;
extern s32 lbl_8064CBC4;
extern s32 lbl_8064CBC8;
extern s32 lbl_8064CBCC;
extern s32 lbl_8064D18C;
extern u32 lbl_8064D5A8;
extern const float lbl_8064E7E0;
extern const float lbl_8064E7E4;
extern const float lbl_8064E7E8;
extern const float lbl_8064E7EC;

extern void *fn_80201BC8(void *object);
extern ObjectInfo *fn_80201B8C(void *object);
extern s32 fn_80038308(void *object, s32 channel, s16 *value);
extern s32 fn_80038464(void *object, s32 channel, s16 *value);
extern void fn_8013033C(void *object, float value);
extern void fn_800AF354(Owner *owner);
extern s32 fn_8006BCE4(Owner *owner);
extern s32 fn_8006BCB4(Owner *owner);
extern void fn_801E7974(void *bits, u32 index);
extern void fn_801E79A0(void *bits, u32 index);
extern s32 fn_801E79FC(u32 *bits, u32 index);
extern s32 fn_80070AD0(void);
extern u64 fn_8020123C(s32 kind, s32 arg1, s32 arg2, s32 arg3);
extern s32 fn_800CAB80(s32 mode);
extern void fn_800EABD8(s32 value);
extern u8 fn_8004736C(s32 value);
extern void fn_8014C23C(u16 kind, u8 variant, s8 strength);
extern void fn_8016ADF0(s16 id, s16 value2, s16 value4);
extern u8 fn_80128EE4(void *owner);
extern s32 fn_80050A20(void);
extern s32 fn_8006BF1C(void *object, const char *name);
extern s32 fn_801AA388(s32 value);
extern void fn_801F74C8(s32 first, s32 second, s32 third);
extern void fn_801441C0(s32 kind, s32 priority, s32 duration);
extern s32 fn_800389E0(void *object, s32 channel, s16 value, s32 propagate);
extern s32 fn_800A04BC(Owner *owner);
extern s32 fn_800462C8(s32 checkState);
extern s32 fn_800467F0(s32 kind, s32 useCurrent);
extern s32 fn_80201B44(void);
extern void *fn_80201814(s32 id);
extern void *fn_801E741C(const char *name);
extern s32 fn_8015C4A4(void *target, s32 selector);
extern void *fn_80158ABC(s32 index, s32 key, float *value);
extern s32 fn_801AC9F4(u16 id, u8 arg4, Vec3 *position, u8 arg8);
extern void fn_801E7DCC(const char *format, ...);
extern void fn_80071550(s32 target, s32 enabled);
extern void fn_801FA748(s32 index, Vec3 *position);
extern void fn_80070B68(void);
extern void fn_800AE8A4(u8 mode);
extern void fn_800AF1C0();
extern void fn_8008A5B8(void *object);

u8 fn_8006BFB4(void *object, Owner *owner)
{
    s16 current;
    s16 maximum;
    s16 limited;
    Vec3 position;
    Vec3 resetPosition;
    const char *names = lbl_80243EE8;
    void *runtime;
    ObjectInfo *info;
    ObjectData *data;
    u8 active;
    u8 oldLevel;
    ModeState *modeState;
    float scale;
    float sanityRatio;
    float value;

    runtime = fn_80201BC8(object);
    fn_80038308(object, 1, &current);
    fn_80038464(object, 1, &maximum);
    info = fn_80201B8C(object);
    if (info != 0) {
        data = info->data;
    } else {
        data = 0;
    }
    value = (float)current;
    sanityRatio = value / (float)maximum;
    owner->sanityRatio = sanityRatio;
    modeState = owner->modeState;
    oldLevel = owner->mode;
    /* Increase the runtime scale as sanity decreases. */
    scale = lbl_8064E7E0;
    value = scale - sanityRatio;
    scale += value;
    fn_8013033C(runtime, scale);
    active = modeState->active;
    if (sanityRatio < lbl_8064E7E4) {
        owner->mode = 3;
    } else if (sanityRatio < lbl_8064E7E8) {
        owner->mode = 2;
    } else if (sanityRatio < lbl_8064E7EC) {
        owner->mode = 1;
    } else {
        owner->mode = 0;
    }
    fn_800AF354(owner);
    if (lbl_8064B824 == 0) {
        owner->mode = 0;
        return 0;
    }
    if (lbl_8064CBC0 != 0) {
        s32 first = fn_8006BCE4(owner);
        s32 second = fn_8006BCB4(owner);
        s32 selected;
        owner->mode = 3;
        fn_801E7974(lbl_8064C4E0, 0x376);
        fn_801E79A0(lbl_8064C4E0, 0x377);
        fn_801E79A0(lbl_8064C4E0, 0x3BF);
        fn_801E79A0(lbl_8064C4E0, 0x1DC);
        if (first != -1) {
            selected = fn_80070AD0();
            if (selected != -1 && selected != first &&
                first != 0x1E && first != 0xC && first != 0x16) {
                fn_8020123C(0x52, 0, data->id, 0);
            }
        } else if (second != -1) {
            selected = fn_80070AD0();
            if (selected != -1 && selected != second &&
                second != 0x1E && first != 0xC && first != 0x16) {
                fn_8020123C(0x52, 0, data->id, 0);
            }
        }
    }
    switch (lbl_803003C8[2]) {
    case 0:
        if (fn_801E79FC(lbl_8064C4E0, 0x2BA) != 0) {
            if (fn_801E79FC(lbl_8064C4E0, 0x36C) == 0) {
                fn_801E7974(lbl_8064C4E0, 0x36C);
            }
            if (sanityRatio > lbl_8064E7EC) {
                if (--lbl_8064B538 == 0) {
                    if (lbl_8064D18C == 0x53) {
                        fn_800CAB80(0);
                        fn_800EABD8(1);
                        lbl_8064B538 = 1;
                    } else {
                        fn_801E79A0(lbl_8064C4E0, 0x2BA);
                        fn_8004736C(0);
                        fn_8014C23C(0, 0, 0);
                        fn_8016ADF0(0xAE9, -1, 1);
                        lbl_8064C8B8 = 0xF;
                    }
                }
            } else {
                lbl_8064B538 = 0xF0;
            }
        }
        if (lbl_8064D18C == 0x5E) {
            s32 blocked;
            u8 rawFlags;
            u32 flags;
            s32 found;
            s32 triggered;
            u16 duration;
            if (lbl_8064C4E4 != 0) {
                rawFlags = fn_80128EE4(lbl_8064C4E4);
            } else {
                rawFlags = 0;
            }
            flags = rawFlags;
            blocked = 1;
            if (fn_80050A20() == 0 && !(flags & 0x51)) {
                blocked = 0;
            }
            /* BoundryRgn01 through BoundryRgn05. */
            found = fn_8006BF1C(lbl_8064C4E4, names + 0x24C);
            found |= fn_8006BF1C(lbl_8064C4E4, names + 0x25C);
            found |= fn_8006BF1C(lbl_8064C4E4, names + 0x26C);
            found |= fn_8006BF1C(lbl_8064C4E4, names + 0x27C);
            found |= fn_8006BF1C(lbl_8064C4E4, names + 0x28C);
            if (found != 0) {
                triggered = fn_801AA388(0);
                if (blocked == 0 && fn_801E79FC(lbl_8064C4E0, 0x2BA) == 0) {
                    if (triggered != 0) {
                        if (++lbl_8064C8BC == 1) {
                            fn_801F74C8(5, 1, 5);
                            duration = 5;
                        } else if (lbl_8064C8BC == 2) {
                            fn_801F74C8(10, 2, 5);
                            duration = 10;
                        } else {
                            fn_801F74C8(20, 3, 5);
                            duration = 20;
                        }
                        if (fn_801E79FC(lbl_8064C4E0, 0x36C) == 0) {
                            fn_801441C0(duration, 0, duration);
                        }
                    }
                    if (lbl_8064C8B8 <= 0 && lbl_8064C8BC > 3) {
                        fn_8016ADF0(0xAE8, -1, 1);
                        fn_801E7974(lbl_8064C4E0, 0x2BA);
                        lbl_8064B538 = 0xF0;
                        fn_80038308(object, 1, &limited);
                        if (limited > 0x19) {
                            fn_800389E0(object, 1, 0x19, 0);
                        }
                    } else {
                        lbl_8064C8B8--;
                    }
                }
            } else {
                lbl_8064C8BC = 0;
            }
        } else {
            fn_800A04BC(owner);
            if (lbl_8064D18C == 0x45 && (u8)lbl_8064D5A8 == 0 &&
                fn_801E79FC(lbl_8064C4E0, 0x376) != 0 &&
                fn_801E79FC(lbl_8064C4E0, 0x377) == 0 &&
                fn_800462C8(1) == 0 && fn_800467F0(lbl_8064D18C, 0) == 0) {
                info = fn_80201B8C(fn_80201814(fn_80201B44()));
                if (info != 0) {
                    if (info->flag9E == 1 && info->flag9F == 1) {
                        /* Resolve SanityMkr99 for the phone event. */
                        s32 index = fn_8015C4A4(fn_801E741C(names + 0x29C), 2);
                        if (index != -1) {
                            ShortVec3 *point = fn_80158ABC(index, 2, 0);
                            if (point != 0) {
                                position.x = point->x;
                                position.y = point->y;
                                position.z = point->z;
                                fn_801AC9F4(0xAC, 0x78, &position, 2);
                                fn_801E7974(lbl_8064C4E0, 0x375);
                            }
                        } else {
                            fn_801E7DCC(names + 0x2A8, 0);
                        }
                    } else {
                        fn_801E79A0(lbl_8064C4E0, 0x375);
                    }
                }
            }
        }
        break;
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x376) == 0 &&
        lbl_803003C8[2] >= 4 && lbl_803003C8[2] != 0x10) {
        fn_801E7974(lbl_8064C4E0, 0x376);
    }
    if (oldLevel != owner->mode) {
        if (owner->mode != 0) {
            fn_80071550(lbl_8064D18C, 1);
        } else {
            fn_80071550(lbl_8064D18C, 0);
        }
        switch (owner->mode) {
        case 3:
            break;
        case 0:
            resetPosition = lbl_802390C8;
            fn_801FA748(2, &resetPosition);
            break;
        case 1:
            if (modeState->pending != 0) {
                fn_80070B68();
                modeState->pending = 0;
            }
            break;
        case 2:
            if (oldLevel == 1) {
                modeState->timer = 5;
                modeState->state = 0;
            }
            break;
        }
    }
    fn_800AE8A4(owner->mode);
    fn_800AF1C0(owner);
    if (lbl_8064CBC4 != 0) {
        fn_8008A5B8((void *)0x1000);
    } else if (lbl_8064CBC8 != 0) {
        fn_8008A5B8((void *)0x100);
    } else if (lbl_8064CBCC != 0) {
        fn_8008A5B8((void *)2);
    }
    return active;
}
