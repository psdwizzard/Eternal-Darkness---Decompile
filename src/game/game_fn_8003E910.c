typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;
typedef float f32;
typedef unsigned long long u64;

#define NULL ((void *)0)

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct OwnerState {
    u8 pad_00[0x9];
    s8 flags;
} OwnerState;

typedef struct ActorState {
    u8 pad_00[0x48];
    s32 partner;
    u8 pad_4C[0x20];
    s32 status;
    u8 pad_70[0x18];
    Vec3 approach;
    Vec3 target;
    u8 pad_A0[0x1C];
    s32 linked;
    u8 pad_C0[0x4];
    f32 charge;
    u8 pad_C8[0x82];
    s16 radius;
    u8 pad_14C[0x2];
    s16 counter;
    u8 pad_150[0x11];
    s8 facing;
    u8 pad_162[0x3];
    u8 hits;
} ActorState;

typedef struct ContextData {
    u8 pad_00[0x4];
    OwnerState *owner;
    u8 pad_08[0x84];
    ActorState *actor;
    u8 pad_90[0x4];
    s32 mode;
    u8 pad_98[0x4];
    s16 phase;
    u8 pad_9E;
    u8 kind;
} ContextData;

void fn_800359A0(s32, s32);
s32 fn_80035FB8(s32, void *, void *, void *, void *, void *);
s32 fn_80036D5C();
void fn_80036DA4(s32, s32);
s32 fn_80036E50(u32);
void fn_80038308(s32, s32, s16 *);
void fn_800389E0(s32, s32, s16, s32);
s32 fn_8003C04C(s32);
void fn_8003C114(s32, u32, s32);
f32 fn_8003C210(s32);
void fn_8003C320(s32, s32);
void fn_8003C6B8(s32, u32, s32);
void fn_8003C758(s32, s32);
void fn_8003CBE4(s32, s32, u32);
s32 fn_8003CD0C(s32, u32, s32);
s32 fn_8003D69C(s32);
void fn_8003D7B4(s32);
void fn_8003D930(s32, s32);
s32 fn_8003DC04(s32, u32, s32, s32, s8, s32);
void fn_8003DD4C(s32, u32, ActorState *, s32);
void fn_8003E214(s32, u32, s32, ActorState *, s32, s32, s8);
void fn_8003E5DC(s32, u32, s32, ActorState *);
void fn_8003E668(s32, u32, s32, ActorState *, s32, Vec3 *, ContextData *, OwnerState *);
s32 fn_800460EC(void);
void fn_80048708(u32);
void fn_80062ED0(s32, u32, s32, s32 *);
void fn_80064B38(s32, s32, s32 *);
s32 fn_800654F8(s32);
void fn_80066754(s32, s32, s32 *);
void fn_80066888(u32, s32, f32, f32);
void fn_80066A0C(s32, s32);
void fn_80066AEC(s32, s32);
void fn_80067180(s32);
void fn_800674E4(s32, s32);
void fn_80067650(s32, s32);
void fn_80067858(s32);
void fn_80067A18(s32);
void fn_80068290(s32, s32, s32 *);
void fn_80068994(s32, s32);
void fn_80068FE0(s32, u32);
s32 fn_8006D344(s32, s32, s32);
s32 fn_8006D444(void);
s32 fn_80072618(Vec3 *, Vec3 *, s32, s32);
void fn_80077880(s32, ActorState *, s32);
void fn_8007791C(s32);
void fn_80077C1C(s32, u32, s32, s32 *);
void fn_80077E14(s32, u32, s32, s32, ActorState *);
void fn_80077F90(u32);
void fn_8009552C(s32, s32, ActorState *);
void fn_800BD194(s32, ActorState *);
void fn_800BD2DC(s32, ActorState *);
void fn_800BDEE4(s32, ActorState *);
void fn_800BE010(s32, ActorState *);
s32 fn_800BE70C(u32, Vec3 *, s32, s32, f32, f32, f32);
void fn_800BE8D4(s32);
s32 fn_800C99B4(u32, s32, s32);
void fn_800C9AD4(s32, u32);
void fn_800C9B08(s32, u32, s32);
void fn_800C9B74(s32, u32);
s32 fn_800C9BA8(u32, ContextData *);
void fn_800C9E50(s32);
s32 fn_800CA13C(u8);
void fn_800CA1BC(s32, u32, s32, s32 *);
void fn_800CA2C8(s32);
s32 fn_800CAF7C(s32);
s32 fn_800CB254(s32, s32, s32, s32, s32);
void fn_800CC860(s32, s32, s32);
void fn_800CF598(s32);
void fn_800E0708(s32, s32, s32);
void fn_800EA0FC(s32, ActorState *, s32, s32, s32 *);
void fn_800EA3A0(s32, ActorState *);
u8 rand(void);
s32 fn_8011EB04(u32);
void fn_8011F114(Vec3 *, u32);
s32 fn_8011F598(u32, s32, s32, s32, void *, s32);
void fn_8011FA8C(u32, s32, s32);
void fn_8011FADC(u32, s32);
s32 fn_8011FAEC(u32);
s32 fn_8011FF38(void);
void fn_80120AD0(u32, s32, s32, s32, f32, f32);
void fn_801261F4(u32);
void fn_80128A84(void *, u16, s32);
void fn_80128BE4(u32);
void fn_80128C28(void *, void *, s32);
void fn_80128C44(void *, void *, s32);
void *fn_80128E30(u32);
s32 fn_80128EAC(u32);
s32 fn_80128F40(u32);
void fn_80128F74(u32, s32);
s32 fn_801290D0(u32);
void *fn_801294DC(u32, s32, s32, s32);
void fn_801296F8(u32, s32);
void fn_8012976C(u32, s32, s32, Vec3 *);
void fn_80129928(u32, Vec3 *);
void fn_80129FD0(u32, s32, s32);
s32 fn_8012A1BC(u32, s32);
u16 fn_8012A1FC(u32, s32);
s32 fn_8012AFC4(u32);
void fn_8012B324(u32);
void fn_8012B344(u32);
void fn_8012C62C(u32, s32, s32 *, s32 *, s32 *, s32);
void fn_8012F58C(u32, s32, s32, s32, s32, s32);
void fn_8012FE10(u32, s32, Vec3 *);
s32 fn_8012FF34(u32, Vec3 *, s32, s32);
void fn_801302BC(u32, s32);
void fn_8014D478(u32, void *, Vec3 *, s32, s32, void *, s32);
u32 fn_80178E94(Vec3 *, Vec3 *);
void fn_801A7228(void);
s32 fn_801A74C0(void);
u32 fn_801A74F8(s32);
void fn_801A7518(s32, s32);
s32 fn_801A7570(s32);
void fn_801A977C(u32, s32);
void fn_801AAE68(s32, s32, s32, void *, s32, s32, s32, u16, f32, s32);
void fn_801AC9F4(s32, s32, Vec3 *, s32);
void fn_801D14CC(s32);
void fn_801E8328(s32, s32);
void fn_802006D4(s32, s32, s32, s32, s32);
s32 fn_80200C10(s32);
s32 fn_80200C20(s32);
s32 fn_80200C28(s32);
s32 fn_80200C38(s32);
void fn_8020104C(s32, s32, s32, s32, f32);
void fn_80201138(s32, s32, s32, s32, s32, f32);
u64 fn_802011D4(s32);
void fn_8020123C(s32, s32, s32, s32);
u32 fn_80201814(s32);
s32 fn_80201B44(void);
s32 fn_80201B54(s32);
s32 fn_80201B5C(u32);
ContextData *fn_80201B8C(s32);
s32 fn_80201B94(s32);
s32 fn_80201B9C(void);
u32 fn_80201BC8(u32);
s32 fn_80201C48(s32);
void fn_80201D14(s32, s32);
void fn_80201D1C(s32, s32);
void fn_80201D2C(s32, s32);
void fn_80201D34(s32, s32);
s32 fn_80201EB8(s32);
u8 fn_80204434(u32, Vec3 *, s32, s16, f32, f32);
void fn_80204844(s32, s32);
void fn_80204FDC(s32);

extern u8 fn_80204810[];
extern Vec3 lbl_80238DE8;
typedef struct NameTable {
    char sceneA[0x14];
    char tag[0xC];
    char fileA[0x18];
    char sceneB[0x10];
    char fileB[0x18];
    char sceneC[0x14];
    char fileC[0xC];
} NameTable;

extern NameTable lbl_8023E7C0;
extern u8 lbl_802FC5BC[];
extern char lbl_8064B488[8];
extern char lbl_8064B490[8];
extern char lbl_8064B498[4];
extern char lbl_8064B49C[4];
extern s32 lbl_8064C7B8;
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
extern const f32 lbl_8064E26C;
extern const f32 lbl_8064E278;
extern const f32 lbl_8064E28C;
extern const f32 lbl_8064E290;
extern const f32 lbl_8064E294;
extern const f32 lbl_8064E2C0;
extern s32 lbl_8064E2E8;
extern s32 lbl_8064E2EC;
extern s32 lbl_8064E2F0;
extern s32 lbl_8064E2F4;
extern s32 lbl_8064E2F8;
extern const f32 lbl_8064E2FC;
extern const f32 lbl_8064E300;
extern const f32 lbl_8064E304;
extern const f32 lbl_8064E308;
extern const f32 lbl_8064E30C;
extern const f32 lbl_8064E310;
extern const f32 lbl_8064E314;
extern const f32 lbl_8064E318;
extern const f32 lbl_8064E31C;
extern const f32 lbl_8064E320;
extern const f32 lbl_8064E324;
extern s32 lbl_80651938;

s32 fn_8003E910(s32 context, s32 state, s32 event, s32 *result) {
    NameTable *names = &lbl_8023E7C0;
    s32 eventType;
    ActorState *actor;
    u32 runtime;
    ContextData *data;
    OwnerState *ownerState;
    s32 handle;
    s32 owner;
    s32 hitInfo[10];
    s32 linkInfo[10];
    Vec3 pos;
    Vec3 effectPos;
    Vec3 dest;
    Vec3 cur;
    Vec3 cur2;
    Vec3 found;
    Vec3 tmp;
    Vec3 tmp2;
    Vec3 tmp3;
    Vec3 tmp4;
    s32 colorC;
    s32 colorB;
    s32 colorA;
    s32 glowC;
    s32 glowB;
    s32 glowA;
    s16 count;
    s32 frame;
    s32 facing;
    s8 bits;
    u8 pending;
    s32 area;
    s32 moveMode;
    s32 now;
    s32 level;
    s32 flags;
    s32 kind;
    s32 ret;
    void *anim;
    s32 value;
    u32 other;
    f32 oldCharge;

    eventType = fn_80200C10(event);
    runtime = fn_80201BC8(context);
    data = fn_80201B8C(context);
    ownerState = data->owner;
    actor = data->actor;
    handle = fn_80201B94(context);
    owner = fn_80201B54(context);
    fn_8011F114(&pos, runtime);
    frame = lbl_8064D5A8 + data->phase;
    facing = data->actor->facing;
    area = fn_80201EB8(context);
    moveMode = fn_8011EB04(runtime);

    if (eventType == 3) {
        fn_8003E668(context, runtime, owner, actor, handle, &pos, data, ownerState);
    }

    if (state == 0) {
        if (eventType == 1) {
            fn_80067858(owner);
            bits = ownerState->flags;
            if (bits & 2) {
                if (area == lbl_8064D18C) {
                    fn_8020123C(8, owner, owner, 0);
                } else {
                    fn_8020123C(0x39, owner, owner, 0);
                }
            } else if (bits & 8) {
                ownerState->flags &= ~8;
                fn_80201D2C(context, 0x21);
                fn_80201D14(context, 1);
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0x39) {
            fn_8012B324(runtime);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_8011FA8C(runtime, 0xC0, 0);
            fn_801E8328(2, context);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800CA2C8(context);
            fn_800E0708(context, 5, 0);
            fn_80204FDC(context);
            fn_800EA3A0(context, actor);
            return 1;
        }
        if (eventType == 0xC9) {
            if (fn_8011FF38() != 0) {
                s32 changed;
                now = lbl_8064D5A8;
                level = 100;
                fn_8011FA8C(runtime, 0, 0x20000000);
                changed = lbl_8064C7B8 != now;
                if (changed) {
                    lbl_8064C7B8 = now;
                }
                if (!changed) {
                    level = 0x32;
                }
                fn_801AAE68(0x1F1, level, 0, &pos, 2, 2, 0, lbl_8064D18C, lbl_8064E2C0, 0);
            }
            return 1;
        }
        if (eventType == 0x3E) {
            flags = fn_80036D5C(context);
            fn_80067858(owner);
            if (flags & 0x20000) {
                fn_801261F4(runtime);
                colorA = lbl_8064E2F0;
                colorB = lbl_8064E2EC;
                colorC = lbl_8064E2E8;
                fn_8012C62C(runtime, 0xF, &colorC, &colorB, &colorA, 0x12);
                fn_8012F58C(runtime, 0xF, 0, 1, 0x1E, 8);
            } else if (flags & 0x08000000) {
                fn_80036DA4(context, flags & ~0x08000000);
                fn_801261F4(runtime);
                glowA = lbl_8064E2F8;
                glowB = lbl_80651938;
                glowC = lbl_8064E2F4;
                fn_8012C62C(runtime, 0xF, &glowC, &glowB, &glowA, 4);
                fn_8011FA8C(runtime, 0, 0x100);
            }
            pending = ownerState->flags;
            if (pending & 1) {
                ownerState->flags = pending & ~1;
                fn_801261F4(runtime);
                fn_80068FE0(context, runtime);
            }
            fn_800BD194(context, actor);
            fn_800C9E50(context);
            fn_801D14CC(owner);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            return 1;
        }
        if (eventType == 0xCB) {
            fn_8003DD4C(context, runtime, actor, event);
            return 1;
        }
        if (eventType == 8) {
            fn_8003C320(context, event);
            return 1;
        }
        if (eventType == 9) {
            fn_8003C758(context, event);
            return 1;
        }
        if (eventType == 0x67) {
            fn_800C9B08(context, runtime, event);
            return 1;
        }
        if (eventType == 0x65) {
            other = fn_80201814(fn_80200C20(event));
            fn_800359A0(context, other);
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_80200C38(event);
            fn_801A7228();
            return 1;
        }
        if (eventType == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_80200C38(event);
            fn_801A7228();
            return 1;
        }
        if (eventType == 0xB) {
            value = fn_80200C38(event);
            if (lbl_8064D18C == 0x27 && actor->linked != 0) {
                fn_8020123C(0xF6, owner, actor->linked, value);
                if (data->mode == 1) {
                    kind = fn_801A74F8(value);
                    fn_801A7518(value, kind * 2);
                }
            }
            fn_80204844(fn_80201B9C(), 0x20);
            if (fn_8006D344(fn_8006D444(), 0x80000, 0) != 0) {
                fn_80067180(context);
                ret = 1;
            } else if (lbl_8064D18C == 0x27 && data->mode == 2) {
                ret = fn_800654F8(fn_80200C38(event));
                fn_8020123C(8, owner, owner, 0);
            } else if (lbl_8064D18C == 0x27 && data->mode == 3) {
                flags = fn_80036D5C(context);
                fn_80036DA4(context, flags | 2);
                ret = fn_800654F8(fn_80200C38(event));
                fn_8020123C(8, owner, owner, 0);
            } else if (fn_801A7570(value) & 0x2000) {
                effectPos = lbl_80238DE8;
                fn_80067180(context);
                if (fn_8011F598(runtime, 0x14, 0, -1, hitInfo, 1) != -1) {
                    fn_8014D478(runtime, &hitInfo[2], &effectPos, 0xF, 0x20, lbl_802FC5BC + 0x18, 6);
                }
            } else {
                ret = fn_800654F8(fn_80200C38(event));
            }
            if (result != NULL) {
                *result = ret;
            }
            return 1;
        }
        if (eventType == 0xE) {
            fn_80068994(context, event);
            return 1;
        }
        if (eventType == 0x27) {
            fn_80064B38(context, event, result);
            return 1;
        }
        if (eventType == 0x1E) {
            fn_8003D930(context, fn_80200C38(event));
            return 1;
        }
        if (eventType == 0x20) {
            fn_80062ED0(context, runtime, event, result);
            return 1;
        }
        if (eventType == 0x6B) {
            if (fn_80200C38(event) != 0) {
                fn_80077C1C(context, runtime, event, result);
            } else if (result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 0x3B) {
            if (data->kind == 0x25) {
                u32 target;
                s32 sender = fn_80200C20(event);
                target = fn_80201814(sender);
                if (target != 0 && (sender == fn_80201B44() || fn_80201B5C(target) == 0x19)) {
                    if (result != NULL) {
                        *result = 1;
                    }
                } else if (result != NULL) {
                    *result = 0;
                }
            } else if (result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 0x4E) {
            if (result != NULL) {
                *result = actor->status == 0;
            }
            return 1;
        }
        if (eventType == 0x82) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 0x3F) {
            fn_80068290(context, event, result);
            return 1;
        }
        if (eventType == 0xE6) {
            fn_80066888(runtime, fn_80200C38(event), lbl_8064E2FC, lbl_8064E300);
            return 1;
        }
        if (eventType == 0x35) {
            fn_80066754(context, event, result);
            return 1;
        }
        if (eventType == 0x37) {
            fn_80066AEC(context, event);
            return 1;
        }
        if (eventType == 0x32) {
            fn_80066A0C(context, event);
            return 1;
        }
        if (eventType == 0xEA) {
            if (data->kind != 0x25) {
                fn_800674E4(context, event);
            }
            return 1;
        }
        if (eventType == 0xEB) {
            fn_80067650(context, event);
            return 1;
        }
        if (eventType == 0x6E) {
            fn_80077880(context, actor, event);
            return 1;
        }
        if (eventType == 0xF3) {
            s32 target = fn_80200C38(event);
            fn_800EA0FC(context, actor, target, event, result);
            return 1;
        }
        if (eventType == 0xD9) {
            if (result != NULL) {
                *result = actor->partner;
            }
            return 1;
        }
    } else if (state == 1) {
        if (eventType == 3) {
            fn_8003CBE4(context, frame, runtime);
            fn_8003DC04(context, runtime, event, frame, facing, 1);
            return 1;
        }
        if (eventType == 0x5A) {
            u32 target = fn_80201814(fn_80200C20(event));
            if (target != 0) {
                other = fn_80201BC8(target);
            } else {
                other = 0;
            }
            if (other != 0 && fn_800460EC() == 0 && fn_800CAF7C(context) != 0) {
                fn_8011F114(&tmp, other);
                cur = tmp;
                if (fn_80204434(runtime, &cur, 0, actor->radius, lbl_8064E304 * actor->radius, lbl_8064E304) == 0) {
                    fn_8011F114(&tmp2, other);
                    actor->target = tmp2;
                    if (fn_8011F598(other, 0, 0, -1, linkInfo, 1) != -1) {
                        fn_8012FE10(other, 0, &dest);
                    } else {
                        dest = cur;
                    }
                    if (fn_8012FF34(runtime, &dest, 4, 4) != 0) {
                        fn_801302BC(runtime, 0x3C);
                    }
                    fn_80201D2C(context, 0x15);
                    fn_80201D14(context, 1);
                }
            }
            return 1;
        }
    } else if (state == 0x15) {
        if (eventType == 1) {
            actor->charge = lbl_8064E294;
            fn_8012B344(runtime);
            return 1;
        }
        if (eventType == 3) {
            if (fn_8003DC04(context, runtime, event, frame, facing, 0) == 0) {
                f32 dist;
                f32 charge;
                level = 2;
                if (moveMode == 8) {
                    level = 3;
                }
                if (lbl_8064D18C == 0xB7) {
                    dist = lbl_8064E308;
                } else {
                    dist = fn_8003C210(context);
                }
                if (fn_800BE70C(runtime, &actor->target, level, 0, dist, lbl_8064E26C, lbl_8064E30C) == 0) {
                    fn_801294DC(runtime, 0xF, 0x25, 1);
                    if (fn_800CAF7C(context) == 0 && moveMode == 1 && fn_8003CD0C(context, runtime, event) != 0) {
                        fn_801296F8(runtime, 0x1FD70);
                        fn_80201D2C(context, 6);
                        fn_80201D14(context, 1);
                    } else {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                        fn_8012B344(runtime);
                    }
                } else {
                    oldCharge = actor->charge;
                    if (fn_800CAF7C(context) == 0 && moveMode == 1) {
                        fn_801296F8(runtime, 0x1FD70);
                    }
                    charge = actor->charge;
                    if (charge < lbl_8064E310) {
                        actor->charge = charge + lbl_8064E314;
                        if (oldCharge <= lbl_8064E318 && actor->charge > lbl_8064E318) {
                            fn_801A977C(runtime, 0x3F);
                        }
                    }
                }
            }
            return 1;
        }
        if (eventType == 0x5A) {
            u32 target = fn_80201814(fn_80200C20(event));
            if (target != 0) {
                other = fn_80201BC8(target);
            } else {
                other = 0;
            }
            if (other != 0 && fn_800460EC() == 0 && fn_800CAF7C(context) != 0) {
                fn_8011F114(&tmp3, other);
                cur2 = tmp3;
                if (fn_80204434(runtime, &cur2, 0, actor->radius, lbl_8064E304 * actor->radius, lbl_8064E304) == 0) {
                    fn_8011F114(&tmp4, other);
                    actor->target = tmp4;
                }
            }
            return 1;
        }
        if (eventType == 2) {
            kind = fn_80128EAC(runtime);
            flags = fn_801290D0(runtime);
            if ((flags & 4) && (kind == 3 || kind == 2)) {
                if (lbl_8064D18C == 0x53) {
                    fn_8012B344(runtime);
                } else {
                    fn_80128F74(runtime, flags & ~4);
                }
            }
            actor->charge = lbl_8064E294;
            return 1;
        }
    } else if (state == 0x2C) {
        if (eventType == 3) {
            u32 dist = fn_80178E94(&pos, &actor->approach);
            flags = fn_8011FAEC(runtime);
            if (dist < 0x3C || (flags & 0x10) || (flags & 0x20)) {
                if (fn_8003CD0C(context, runtime, event) != 0) {
                    fn_801296F8(runtime, 0x1FD70);
                } else {
                    fn_80201D2C(context, 1);
                    fn_80201D14(context, 1);
                }
            } else if (fn_8012AFC4(runtime) != 0) {
                fn_80129928(runtime, &actor->approach);
            } else {
                fn_8003C210(context);
                fn_8012976C(runtime, 2, 0x21, &actor->approach);
                fn_801296F8(runtime, 0x1FD70);
            }
            return 1;
        }
    } else if (state == 0x3E) {
        if (eventType == 1) {
            fn_8009552C(context, owner, actor);
            return 1;
        }
        if (eventType == 3) {
            return 1;
        }
    } else if (state == 0x3F) {
        if (eventType == 3) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (state == 3) {
        if (eventType == 3) {
            fn_800BE010(context, actor);
            if (fn_80201C48(handle) != 0) {
                fn_800BDEE4(context, actor);
            }
            fn_8003E214(context, runtime, owner, actor, event, frame, facing);
            return 1;
        }
        if (eventType == 0x66) {
            fn_8012B344(runtime);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (state == 6) {
        if (eventType == 12) {
            if ((rand() & 3) && fn_800CAF7C(context) == 0 && moveMode == 1) {
                if ((rand() & 1) && fn_80072618(&pos, &found, 0x190, 4) != 0) {
                    actor->approach = found;
                    fn_80201D2C(context, 0x2C);
                    fn_80201D14(context, 1);
                } else if (fn_80072618(&pos, &found, 0, 4) != 0) {
                    actor->target = found;
                    fn_80201D2C(context, 0x15);
                    fn_80201D14(context, 1);
                } else {
                    fn_80201D2C(context, 1);
                    fn_80201D14(context, 1);
                }
            } else if (fn_800CAF7C(context) == 0 && moveMode == 1 && fn_8003CD0C(context, runtime, event) != 0) {
                fn_801296F8(runtime, 0x1FD70);
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, lbl_8064B488, names->tag, lbl_8064B490, names->fileA) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 13) {
            return 1;
        }
    } else if (state == 7) {
        if (eventType == 0x36) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, lbl_8064B498, names->tag, lbl_8064B490, names->fileA) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
    } else if (state == 0x2F) {
        if (eventType == 1) {
            fn_800E0708(context, 0xB4, 1);
            fn_800CA2C8(context);
            return 1;
        }
        if (eventType == 3) {
            if ((lbl_8064D5A8 & 0xF) == 0) {
                s32 next;
                fn_80038308(context, 0, &count);
                next = count - 1;
                count = (0 > next) ? 0 : next;
                fn_800389E0(context, 0, count, 0);
            }
            if ((u8)lbl_8064D5A8 == 0) {
                fn_801AAE68(1, 0x50, 0, &pos, 2, 2, 0, lbl_8064D18C, lbl_8064E2C0, 0);
            }
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (eventType == 0x4E) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        }
        if (eventType == 0xCB) {
            return 1;
        }
        if (eventType == 9) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0x65) {
            return 1;
        }
        if (eventType == 0xB) {
            return 1;
        }
        if (eventType == 0x27) {
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0x3B) {
            return 1;
        }
        if (eventType == 0x82) {
            return 1;
        }
        if (eventType == 0x3F) {
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0x37) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
    } else if (state == 0x5F) {
        if (eventType == 3) {
            fn_800C9B74(context, runtime);
            return 1;
        }
        if (eventType == 0x68) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 2) {
            fn_800C9AD4(context, runtime);
            return 1;
        }
        if (eventType == 0x69) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0x3F) {
            return 1;
        }
    } else if (state == 0x21) {
        if (eventType == 1) {
            if (fn_8003D69C(owner) == 4) {
                fn_800E0708(context, 0x1E, 0);
            }
            return 1;
        }
        if (eventType == 0x3D) {
            if (fn_8003D69C(owner) == 4) {
                fn_8020123C(0x39, owner, owner, 0);
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, names->sceneB, names->tag, lbl_8064B490, names->fileB) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 8) {
            flags = fn_80036D5C(context);
            if (area != lbl_8064D18C) {
                fn_801E8328(2, context);
                fn_80201D34(context, 0);
                fn_80201D1C(context, 1);
            } else if (flags & 0x80) {
                fn_8003C6B8(context, runtime, owner);
            } else {
                s32 level;
                anim = fn_80128E30(runtime);
                kind = fn_80128EAC(runtime);
                level = fn_80128F40(runtime) >> 17;
                if (data->mode == 2 && ((level < 0x20 && kind == 0x54) || (kind == 0x2A && level > 10))) {
                    fn_8003C320(context, event);
                } else if (kind == 0x54) {
                    s32 frames = fn_8012A1BC(runtime, 0x54);
                    fn_80201138(0x11, context, 8, -1, 0, lbl_8064E28C);
                    fn_80128A84(anim, 0, frames);
                    fn_80201D2C(context, 8);
                    fn_80201D14(context, 1);
                } else if ((kind == 0x2A && level < 0x10) || (kind == 0x29 && level < 0x23)) {
                    fn_80201138(0x11, context, 8, -1, 0, lbl_8064E28C);
                    fn_80129FD0(runtime, 0x20000, 0);
                    fn_80128A84(anim, 0, 2);
                    fn_80201D2C(context, 8);
                    fn_80201D14(context, 1);
                } else if (result != NULL) {
                    *result = fn_802011D4(event) & 0xFFFFFFFF;
                }
            }
            return 1;
        }
        if (eventType == 0x19) {
            fn_80201EB8(context);
            if (fn_8003D69C(owner) == 4) {
                s32 frames;
                void *rise = fn_801294DC(runtime, 0x53, 0x20, 0xA);
                if (rise != NULL) {
                    frames = fn_8012A1BC(runtime, 0x53);
                    fn_80201138(0x11, context, 8, -1, 0, lbl_8064E28C);
                    fn_80128A84(rise, 0, frames);
                    fn_80201D2C(context, 8);
                    fn_80201D14(context, 1);
                }
            } else {
                u16 start;
                void *wait = fn_801294DC(runtime, 0x2A, 0x20, 8);
                if (wait != NULL) {
                    s32 length;
                    start = rand() + 1;
                    length = fn_8012A1FC(runtime, 0x2A) + 1;
                    fn_80128A84(wait, start, length);
                    fn_80128C44(wait, fn_80204810, (owner << 8) | 7);
                    fn_80128C28(wait, fn_80204810, (owner << 8) | 0x38);
                }
            }
            return 1;
        }
        if (eventType == 0x38) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xB) {
            if (fn_8003D69C(owner) != 4 && result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 0x27) {
            if (fn_8003D69C(owner) != 4 && result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 0x1E) {
            if (fn_800C99B4(runtime, 0x2A, 0x1E) != 0 && result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 0x35) {
            if (fn_800C99B4(runtime, 0x2A, 0x1E) != 0 && result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0x37) {
            return 1;
        }
        if (eventType == 9) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0x3F) {
            return 1;
        }
        if (eventType == 2) {
            return 1;
        }
    } else if (state == 0x20) {
        if (eventType == 5) {
            kind = fn_80128EAC(runtime);
            flags = fn_801290D0(runtime);
            if (fn_80128E30(runtime) != NULL && kind == 0xF && (flags & 1)) {
                fn_8012B344(runtime);
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, lbl_8064B49C, names->tag, lbl_8064B490, names->fileA) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            fn_8020123C(5, owner, owner, 0);
            return 1;
        }
        if (eventType == 2) {
            fn_802006D4(owner, owner, 0x20, 5, 0);
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
    } else if (state == 0x34) {
        if (eventType == 1) {
            flags = fn_80036D5C(context);
            fn_80036DA4(context, flags & ~0x1C0);
            actor->counter = 0;
            return 1;
        }
        if (eventType == 0x72) {
            fn_80077E14(context, runtime, event, owner, actor);
            return 1;
        }
        if (eventType == 0x6F) {
            flags = fn_80036D5C(context);
            fn_80036DA4(context, flags | 0x40);
            return 1;
        }
        if (eventType == 0x75) {
            flags = fn_80036D5C(context);
            fn_80036DA4(context, flags | 0x100);
            return 1;
        }
        if (eventType == 0x70) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            fn_8020123C(0x74, owner, actor->partner, 0);
            fn_8020123C(0x74, owner, owner, 0);
            fn_800BD2DC(context, actor);
            return 1;
        }
        if (eventType == 0x74) {
            fn_8012B344(runtime);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 7) {
            fn_8020123C(0x74, owner, actor->partner, 0);
            return 1;
        }
        if (eventType == 0x6C) {
            s32 strong;
            flags = fn_80036D5C(context);
            if (actor->hits >= 8 && !(flags & 0x100)) {
                strong = 1;
            } else {
                strong = 0;
            }
            actor->hits = 0;
            flags = fn_80036D5C(context);
            fn_80036DA4(context, flags & ~0x40);
            if (strong) {
                anim = fn_801294DC(runtime, 0x7F, 0x20, 8);
                if (anim != NULL) {
                    fn_80128C28(anim, fn_80204810, (owner << 8) | 0x70);
                } else {
                    fn_80201D2C(context, 1);
                    fn_80201D14(context, 1);
                }
                actor->partner = 0;
            } else {
                anim = fn_801294DC(runtime, 0x7E, 0x20, 8);
                if (anim != NULL) {
                    fn_80128C44(anim, fn_80204810, (owner << 8) | 0x71);
                    fn_80128C28(anim, fn_80204810, (owner << 8) | 0x71);
                    fn_80201D2C(context, 0x35);
                    fn_80201D14(context, 1);
                }
            }
            return 1;
        }
        if (eventType == 0x20) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        }
        if (eventType == 0x35) {
            fn_8020123C(0xF7, owner, actor->partner, 0);
            fn_8020123C(0x74, owner, actor->partner, 0);
            fn_8020123C(0x74, owner, owner, 0);
            if (result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 3) {
            if (fn_801290D0(runtime) & 0x800) {
                actor->counter++;
                if (actor->counter > 6) {
                    fn_80128BE4(runtime);
                }
            }
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
        if (eventType == 0x2C) {
            return 1;
        }
        if (eventType == 0x69) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
    } else if (state == 0x35) {
        if (eventType == 0x71) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_8020123C(0x74, owner, owner, 0);
            return 1;
        }
        if (eventType == 3) {
            flags = fn_80036D5C(context);
            if ((lbl_8064D5A8 & 7) == 0 && !(flags & 0x80)) {
                fn_80077F90(runtime);
            }
            return 1;
        }
        if (eventType == 0x74) {
            fn_8012B344(runtime);
            fn_80048708(runtime);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800BD2DC(context, actor);
            fn_80077880(context, actor, event);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0x2C) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
    } else if (state == 0x37) {
        if (eventType == 1) {
            fn_801AC9F4(0x19, 0x64, &pos, 2);
            return 1;
        }
        if (eventType == 0x77) {
            fn_8007791C(context);
            fn_800389E0(context, 0, 0, 1);
            fn_8020104C(0x39, owner, owner, 0, lbl_8064E290);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            return 1;
        }
        if (eventType == 0xE6) {
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0x2C) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
    } else if (state == 9) {
        if (eventType == 1) {
            fn_800CC860(context, 1, 0);
            fn_800BE8D4(owner);
            fn_8011FA8C(runtime, 0xC0, 0);
            return 1;
        }
        if (eventType == 3) {
            fn_8003E5DC(context, runtime, owner, actor);
            return 1;
        }
        if (eventType == 0xC1) {
            if (result != NULL) {
                *result = fn_800C9BA8(runtime, data);
            }
            return 1;
        }
        if (eventType == 0x2F) {
            fn_80201D2C(context, 0x1F);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xB) {
            s32 target = fn_80200C38(event);
            if (fn_801A74C0() & 0x20) {
                s32 done = fn_800654F8(target);
                fn_8020123C(0x2F, owner, owner, 0);
                fn_8020104C(0x31, owner, owner, 0, lbl_8064E278);
                if (result != NULL) {
                    *result = done;
                }
            } else if (fn_801A7570(target) & 0x2000) {
                fn_80067180(context);
            }
            return 1;
        }
        if (eventType == 0x35) {
            fn_80066888(runtime, fn_80200C38(event), lbl_8064E2FC, lbl_8064E300);
            return 1;
        }
        if (eventType == 0x18) {
            if (fn_800CB254(context, 0x64, 0, lbl_8064D18C, 1) == 0 && area == lbl_8064D18C) {
                if (runtime != 0) {
                    flags = fn_8011FAEC(runtime);
                    fn_8011FADC(runtime, flags | 0xC0);
                }
                fn_8012B344(runtime);
                anim = fn_801294DC(runtime, 0x29, 0x20, 8);
                if (anim != NULL) {
                    fn_80128C44(anim, fn_80204810, (owner << 8) | 7);
                    fn_80128C28(anim, fn_80204810, (owner << 8) | 0x38);
                    fn_800389E0(context, 0, 0xA, 1);
                    fn_80201D2C(context, 0x21);
                    fn_80201D14(context, 1);
                }
            } else {
                fn_802006D4(owner, owner, 9, 0x18, 0);
                fn_80201138(0x18, context, 9, -1, 0, lbl_8064E31C);
            }
            return 1;
        }
        if (eventType == 8) {
            fn_80201D2C(context, 0x1F);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x3B) {
            u32 target;
            target = fn_80201814(fn_80200C20(event));
            if (target != 0 && (fn_80036E50(target) == 0x1F || fn_80036E50(target) == 0x20 || fn_80036E50(target) == 0x21) && result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 2) {
            fn_802006D4(owner, owner, 9, 0x18, 0);
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0x3F) {
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
        if (eventType == 0x37) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 9) {
            return 1;
        }
        if (eventType == 0x27) {
            return 1;
        }
        if (eventType == 0x69) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
    } else if (state == 0x1F) {
        if (eventType == 1) {
            s32 frames;
            s32 move = fn_80128EAC(runtime);
            frames = fn_8012A1BC(runtime, move);
            fn_80128F40(runtime);
            fn_800BE8D4(owner);
            fn_800CC860(context, 2, 3);
            fn_801A977C(runtime, 0x33);
            fn_800E0708(context, 0x1E, 1);
            fn_800CA2C8(context);
            fn_80204FDC(context);
            fn_8020104C(0x11, owner, owner, 0, lbl_8064E320);
            fn_80128A84(fn_80128E30(runtime), 0, frames);
            return 1;
        }
        if (eventType == 3) {
            fn_8003E5DC(context, runtime, owner, actor);
            return 1;
        }
        if (eventType == 0x30) {
            s32 target = fn_80200C38(event);
            if (result != NULL) {
                *result = fn_800654F8(target);
            }
            return 1;
        }
        if (eventType == 0x35) {
            fn_80066888(runtime, fn_80200C38(event), lbl_8064E2FC, lbl_8064E300);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800BD2DC(context, actor);
            fn_800EA3A0(context, actor);
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (eventType == 0x11) {
            fn_80120AD0(runtime, 0, 0, 0x101, lbl_8064E324, lbl_8064E294);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            fn_800CF598(context);
            return 1;
        }
        if (eventType == 0x31) {
            fn_8003C114(context, runtime, owner);
            return 1;
        }
        if (eventType == 0xB) {
            u32 target = fn_80200C38(event);
            if (target != 0 && (fn_801A7570(target) & 0x2000)) {
                fn_80067180(context);
            }
            return 1;
        }
        if (eventType == 7) {
            fn_80035FB8(context, names->sceneA, names->sceneC, names->tag, names->fileC, names->fileC);
            return 1;
        }
        if (eventType == 0x3B) {
            u32 target;
            target = fn_80201814(fn_80200C20(event));
            if (target != 0 && (fn_80036E50(target) == 0x1F || fn_80036E50(target) == 0x20 || fn_80036E50(target) == 0x21) && result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 0x4E) {
            return 1;
        }
        if (eventType == 0x18) {
            return 1;
        }
        if (eventType == 0x19) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0x3F) {
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0x37) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 8) {
            return 1;
        }
        if (eventType == 9) {
            return 1;
        }
        if (eventType == 0xB) {
            return 1;
        }
        if (eventType == 0x27) {
            return 1;
        }
        if (eventType == 0x69) {
            return 1;
        }
        if (eventType == 0x3E) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0xEA) {
            return 1;
        }
    } else if (state == 8) {
        if (eventType == 1) {
            fn_8011FA8C(runtime, 0xC0, 0);
            fn_800BE8D4(owner);
            fn_800CC860(context, 1, 0);
            fn_800E0708(context, fn_800CA13C(data->kind) * 2, 0);
            fn_800CA2C8(context);
            fn_80204FDC(context);
            return 1;
        }
        if (eventType == 3) {
            fn_8003E5DC(context, runtime, owner, actor);
            return 1;
        }
        if (eventType == 0xC2) {
            fn_800CA1BC(context, runtime, event, result);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_800EA3A0(context, actor);
            fn_800BD2DC(context, actor);
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (eventType == 0x11) {
            if (fn_8003C04C(context) != 0) {
                s32 level = fn_80128F40(runtime) >> 17;
                fn_80128A84(fn_80128E30(runtime), 0, level);
                fn_80120AD0(runtime, 0, 0, 0x101, lbl_8064E324, lbl_8064E294);
                fn_800CF598(context);
                fn_800EA3A0(context, actor);
                fn_8003D7B4(owner);
                fn_80067A18(owner);
                fn_80201D34(context, 0x15);
                fn_80201D1C(context, 1);
            }
            return 1;
        }
        if (eventType == 0x33) {
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (eventType == 0xC1) {
            if (result != NULL) {
                *result = fn_800C9BA8(runtime, data);
            }
            return 1;
        }
        if (eventType == 0x2F) {
            fn_80201D2C(context, 0x1F);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xB) {
            s32 target = fn_80200C38(event);
            if (fn_801A74C0() & 0x20) {
                s32 done = fn_800654F8(target);
                fn_8020123C(0x2F, owner, owner, 0);
                fn_8020104C(0x31, owner, owner, 0, lbl_8064E278);
                if (result != NULL) {
                    *result = done;
                }
            } else if (fn_801A7570(target) & 0x2000) {
                fn_80067180(context);
            }
            return 1;
        }
        if (eventType == 0x35) {
            fn_80066888(runtime, fn_80200C38(event), lbl_8064E2FC, lbl_8064E300);
            return 1;
        }
        if (eventType == 0x4E) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        }
        if (eventType == 0x3B) {
            u32 target;
            target = fn_80201814(fn_80200C20(event));
            if (target != 0 && (fn_80036E50(target) == 0x1F || fn_80036E50(target) == 0x20 || fn_80036E50(target) == 0x21) && result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 2) {
            fn_802006D4(owner, owner, 8, 0x11, 0);
            return 1;
        }
        if (eventType == 0x18) {
            return 1;
        }
        if (eventType == 0x19) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0x3F) {
            return 1;
        }
        if (eventType == 0x1E) {
            return 1;
        }
        if (eventType == 0x37) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 8) {
            return 1;
        }
        if (eventType == 9) {
            return 1;
        }
        if (eventType == 0x27) {
            return 1;
        }
        if (eventType == 0x69) {
            return 1;
        }
        if (eventType == 0x3E) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0xEA) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
