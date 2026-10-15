typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;
typedef float f32;
typedef unsigned long long u64;

#define NULL 0

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct OwnerState {
    u8 pad_00[0x28];
    s32 linked;
    s32 flags;
    s16 timer;
} OwnerState;

typedef struct ActorState {
    s32 flags;
    u8 pad_04[0x44];
    s32 partner;
    u8 pad_4C[0x8];
    s32 holder;
    u8 pad_58[0x3C];
    Vec3 target;
    u8 pad_A0[0x28];
    s32 effect;
    u8 pad_CC[0x82];
    s16 grabCount;
    s16 cooldown;
    u8 pad_152[0xA];
    s16 struggle;
    s16 hitCount;
    u8 pad_160;
    s8 facing;
    u8 pad_162;
    s8 stun;
    u8 pad_164;
    u8 hits;
} ActorState;

typedef struct ContextData {
    u8 pad_00[0x68];
    OwnerState *owner;
    u8 pad_6C[0x20];
    ActorState *actor;
    u8 pad_90[0xC];
    s16 phase;
    u8 pad_9E;
    u8 kind;
} ContextData;

typedef struct EffectData {
    u8 pad_00[0x18];
    f32 amount;
    f32 values[1];
} EffectData;

typedef struct NameTable {
    char pad_00[0x10];
    char tag[0xC];
    char file[0xD4];
    char sceneA[0x14];
    char sceneB[0x10];
    char sceneC[0xC];
    char sceneD[0x8];
} NameTable;

typedef struct GameState {
    u8 pad_00[0x8];
    s32 mode;
} GameState;

typedef union Color {
    u8 channels[4];
    u32 rgba;
} Color;

s32 fn_80035FB8(s32, void *, void *, void *, void *, void *);
s32 fn_80036D5C(s32);
void fn_80036DA4(s32, s32);
void fn_80038308(s32, s32, s16 *);
void fn_800389E0(s32, s32, s16, s32);
void fn_8003DD4C(s32, u32, ActorState *, s32);
void fn_8003DED0(s32, u32, ActorState *);
void fn_8003E5DC(s32, u32, s32, ActorState *);
void fn_80048708(u32);
void fn_80066754(s32, s32, s32 *);
void fn_80066888(u32, s32, f32, f32);
void fn_80068994(s32, s32);
void fn_80077880(s32, ActorState *, s32);
void fn_8007791C(s32);
void fn_80077C1C(s32, u32, s32, s32 *);
void fn_80077E14(s32, u32, s32, s32, ActorState *);
void fn_80077F90(u32);
s32 fn_80092BBC(s32, u32, ContextData *);
s32 fn_80092C30(s32, OwnerState *);
void fn_80092CCC(s32, s32, ActorState *);
void fn_80092D90(s32, u32, s32, s32, ActorState *);
s32 fn_800931D0(s32, s32, ActorState *);
void fn_800933A0(s32, u32, s32, s32 *);
void fn_800934A0(s32, u32, s32, s32 *);
EffectData *fn_800935CC(s32, void *, s32, s32);
void fn_80093C04(s32, u32, s32, s32 *);
void fn_80093D20(s32, s32);
void fn_80093F6C(s32, u32, s32, ActorState *, s32, s32, s8);
void fn_80094DD0(s32, u32, s32);
void fn_8009552C(s32, s32, ActorState *);
void fn_800955A4(s32, s32, ActorState *);
void fn_80095654(s32, s32, ActorState *, ContextData *, s32);
void fn_80095774(s32, s32, ActorState *, ContextData *, s32);
void fn_80095894(s32, u32, s32, ActorState *);
void fn_80095954(s32, u32, s32, ActorState *, s32);
void fn_80095C20(s32, u32, s32, OwnerState *);
void fn_80095FDC(s32, u32, s32, OwnerState *, s32);
void fn_80096208(s32, u32, s32, OwnerState *, s32);
void fn_80096690(s32, s32);
void fn_80096710(s32, s32, ActorState *, ContextData *, s32);
void fn_80096830(s32, s32, u32, s32);
void fn_8009697C(s32, s32, u32, s32);
void fn_80096D58(s32, u32, s32);
void fn_80096F04(s32, s32, u32, s32, OwnerState *, ContextData *, s32 *);
void fn_80096FDC(s32, s32, OwnerState *);
void fn_80097014(s32, s32, s32, OwnerState *, ContextData *, s32 *);
void fn_800971A0(s32, s32, s32, OwnerState *, ContextData *, s32 *);
void fn_800972D0(s32, s32, OwnerState *, ContextData *, s32 *);
void fn_800BD194(s32, ActorState *);
void fn_800BD2DC(s32, ActorState *);
void fn_800BDEE4(s32, ActorState *);
void fn_800BE010(s32, ActorState *);
s32 fn_800BE70C(u32, Vec3 *, s32, s32, f32, f32, f32);
void fn_800BE8D4(s32);
void fn_800C9AD4(s32, u32);
void fn_800C9B08(s32, u32, s32);
void fn_800C9B74(s32, u32);
void fn_800C9E50(s32);
void fn_800CA2C8(s32);
void fn_800CC650(s32, s32, s32, s16);
void fn_800CC860(s32, s32, s32);
s32 fn_800DE354(void);
void fn_800EA0FC(s32, ActorState *, s32, s32, s32 *);
void fn_800EA3A0(s32, ActorState *);
void fn_8011F114(Vec3 *, u32);
void fn_8011FA8C(u32, s32, s32);
void fn_8011FABC(u32, s32, s32);
void fn_8011FADC(u32, s32);
s32 fn_8011FAEC(u32);
s32 fn_8011FAF4(u32);
void fn_801261F4(u32);
void fn_80128BE4(u32);
void fn_80128C28(void *, void *, s32);
void fn_80128C44(void *, void *, s32);
void *fn_80128E30(u32);
s32 fn_80128EAC(u32);
void fn_80128F74(u32, s32);
s32 fn_801290D0(u32);
void *fn_801294DC(u32, s32, s32, s32);
void fn_8012B324(u32);
void fn_8012B344(u32);
f32 fn_8012B750(u32);
void fn_8012B7A0(u32, f32);
void *fn_8012C62C(u32, s32, Color *, Color *, Color *, s32);
void fn_8012F58C(u32, s32, s32, s32, s32, s32);
s32 fn_8013017C(u32);
void fn_801301B0(u32, s32, s32);
s32 fn_801305D4(u32);
f32 fn_80179F20(f32);
f32 fn_80179FE4(f32 *, s32, f32);
s32 fn_8017A010(f32 *, s32, f32, f32, f32);
void fn_8017A12C(f32 *, f32, f32);
s32 fn_801A717C(void);
void fn_801A7228(s32);
s32 fn_801A7488(void);
void fn_801A74A0(s32, s32);
void fn_801A74A8(s32, s32);
void fn_801A7518(s32, s32);
void fn_801A7538(s32, s32);
void fn_801A977C(u32, s32);
void fn_801AAE68(s32, s32, s32, void *, s32, s32, s32, u16, f32, s32);
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
s32 fn_80201814(s32);
s32 fn_80201B44(void);
s32 fn_80201B54(s32);
ContextData *fn_80201B8C(s32);
void *fn_80201B94(s32);
u32 fn_80201BC8(u32);
s32 fn_80201C48(void *);
void fn_80201D14(s32, s32);
void fn_80201D1C(s32, s32);
void fn_80201D2C(s32, s32);
void fn_80201D34(s32, s32);
void fn_80201DD8(void *, s32);
s32 fn_80201EB8(s32);
void fn_80204FDC(s32);

extern u8 fn_80204810[];
extern NameTable lbl_80245238;
extern GameState lbl_803003C8;
extern char lbl_8064B5F8[8];
extern char lbl_8064B600[8];
extern char lbl_8064B608[4];
extern char lbl_8064B60C[8];
extern char lbl_8064B614[4];
extern s32 lbl_8064C55C;
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
extern const f32 lbl_8064EC78;
extern const f32 lbl_8064EC7C;
extern const f32 lbl_8064ECA8;
extern const f32 lbl_8064ECAC;
extern const f32 lbl_8064ECC4;
extern Color lbl_8064ECEC;
extern Color lbl_8064ECF0;
extern Color lbl_8064ECF4;
extern Color lbl_8064ECF8;
extern Color lbl_8064ECFC;
extern const f32 lbl_8064ED00;
extern const f32 lbl_8064ED04;
extern const f32 lbl_8064ED08;
extern const f32 lbl_8064ED0C;
extern const f32 lbl_8064ED10;
extern Color lbl_806519E0;


static inline void DebugBreakpoint(void) {
    /* ASM: nop preserves a retail debug breakpoint that an empty C statement removes. */
    asm { nop }
}

typedef struct ColorCopy {
    Color source;
    Color value;
} ColorCopy;

static inline Color *PrepareColor(ColorCopy *dest, const Color *source) {
    dest->source = *source;
    dest->value = dest->source;
    return &dest->value;
}

s32 fn_800973E0(register s32 context, s32 state, register s32 event, register s32 *result) {
    NameTable *names = &lbl_80245238;
    ContextData *data;
    OwnerState *ownerState;
    s32 frame;
    u32 ctrlFlags;
    s32 flags;
    u32 runtime;
    s32 facing;
    s32 eventType;
    void *handle;
    ActorState *actor;
    s32 owner;
    struct {
        s16 count;
        ColorCopy finalA, finalB, finalC;
        ColorCopy initialA, initialB, initialC;
        f32 delta3, angle3;
        f32 delta2, angle2;
        f32 delta1, angle1;
        Vec3 pos;
    } temps;

    eventType = fn_80200C10(event);
    runtime = fn_80201BC8(context);
    data = fn_80201B8C(context);
    ownerState = data->owner;
    actor = data->actor;
    handle = fn_80201B94(context);
    owner = fn_80201B54(context);
    fn_8011F114(&temps.pos, runtime);
    frame = lbl_8064D5A8 + data->phase;
    facing = data->actor->facing;
    ctrlFlags = fn_8011FAEC(runtime);
    flags = fn_80036D5C(context);

    if (eventType == 3) {
        s32 count;
        if (actor->cooldown >= 1) {
            count = actor->cooldown - 1;
        } else {
            count = 0;
        }
        actor->cooldown = count;
        fn_8003DED0(context, runtime, actor);
        if (ctrlFlags & 0x10) {
            fn_8011FA8C(runtime, 0x10, 0);
            if (++actor->struggle > 0x46) {
                actor->stun = 4;
                actor->struggle = 0;
            }
        } else if (actor->struggle != 0) {
            if (actor->struggle - 1 < 0) {
                count = 0;
            } else {
                count = actor->struggle - 1;
            }
            actor->struggle = count;
        }
        if (actor->stun > 0) {
            count = actor->stun - 1;
        } else {
            count = 0;
        }
        actor->stun = count;
        if ((fn_8013017C(runtime) & 0x40) && fn_801305D4(runtime) == 0) {
            fn_801301B0(runtime, 0x40, 0);
        }
    }

    if (state == 0) {
        if (eventType == 1) {
            fn_8020123C(0x3B, owner, owner, 0);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x20) {
            fn_80096F04(owner, context, runtime, event, ownerState, data, result);
            return 1;
        }
        if (eventType == 0xAC) {
            fn_80095774(context, owner, actor, data, event);
            return 1;
        }
        if (eventType == 0xBA) {
            fn_80096690(owner, 0x10);
            return 1;
        }
        if (eventType == 0xB6) {
            fn_8009697C(owner, context, runtime, event);
            return 1;
        }
        if (eventType == 0x32) {
            fn_80096FDC(context, event, ownerState);
            return 1;
        }
        if (eventType == 0x67) {
            fn_800C9B08(context, runtime, event);
            return 1;
        }
        if (eventType == 0xAD) {
            fn_80096690(owner, 0x14);
            return 1;
        }
        if (eventType == 0xA7) {
            fn_800933A0(context, runtime, event, result);
            return 1;
        }
        if (eventType == 0x82) {
            s32 ready;
            u8 mode = fn_80200C38(event);
            ready = 0;
            if (mode == 2) {
                ready = 1;
            }
            if (result != NULL) {
                *result = ready;
            }
            return 1;
        }
        if (eventType == 0xCB) {
            if (!(ownerState->flags & 4)) {
                fn_8003DD4C(context, runtime, actor, event);
            }
            return 1;
        }
        if (eventType == 0x3B) {
            if (result != NULL) {
                *result = !(ownerState->flags & 4);
            }
            return 1;
        }
        if (eventType == 0x7D) {
            if (fn_80200C38(event) != 0) {
                fn_80093C04(context, runtime, event, result);
            } else if (result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            ownerState->flags &= ~0x200;
            if (lbl_803003C8.mode != 9 || lbl_8064C55C == 0) {
                ownerState->flags &= ~0x800;
            }
            return 1;
        }
        if (eventType == 0x3E) {
            s32 value;
            if (fn_80036D5C(context) & 0x20000) {
                fn_801261F4(runtime);
                fn_8012C62C(runtime, 0xF,
                PrepareColor(&temps.initialC, &lbl_8064ECEC),
                PrepareColor(&temps.initialB, &lbl_8064ECF0),
                PrepareColor(&temps.initialA, &lbl_8064ECF4), 0x12);
                fn_8012F58C(runtime, 0xF, 0, 1, 0x1E, 8);
            }
            fn_800BD194(context, actor);
            fn_80096D58(context, runtime, event);
            fn_800C9E50(context);
            return 1;
        }
        if (eventType == 0xE) {
            fn_80068994(context, event);
            return 1;
        }
        if (eventType == 0x27) {
            fn_800971A0(owner, context, event, ownerState, data, result);
            return 1;
        }
        if (eventType == 8) {
            if (!(ownerState->flags & 4)) {
                fn_80093D20(context, event);
            }
            return 1;
        }
        if (eventType == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (eventType == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (eventType == 0xB) {
            fn_80097014(owner, context, event, ownerState, data, result);
            return 1;
        }
        if (eventType == 0xE6) {
            s32 value;
            value = fn_80200C38(event);
            if (fn_801A7488() == -1) {
                fn_80066888(runtime, value, lbl_8064ECA8, lbl_8064ECAC);
            } else {
                fn_80066754(context, event, result);
            }
            return 1;
        }
        if (eventType == 0x35) {
            s32 value;
            s32 sound;
            value = fn_80200C38(event);
            sound = fn_801A7488();
            if (sound == -1) {
                fn_80066888(runtime, value, lbl_8064ECA8, lbl_8064ED00);
            } else {
                if (sound == 0x44 || sound == 0xF || sound == 0x10 || !(ownerState->flags & 4)) {
                    fn_80066754(context, event, result);
                }
            }
            return 1;
        }
        if (eventType == 0x33) {
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (eventType == 0x39) {
            fn_8012B324(runtime);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
        if (eventType == 0x93) {
            fn_800972D0(context, event, ownerState, data, result);
            return 1;
        }
        if (eventType == 0x6B) {
            if (!(ownerState->flags & 4) && !(flags & 0x80) && !(flags & 0x8000)) {
                if (fn_80200C38(event) != 0) {
                    if (fn_80092BBC(context, runtime, data) != 0) {
                        ownerState->flags |= 0x400;
                        ownerState->flags |= 0x800;
                    }
                    fn_80077C1C(context, runtime, event, result);
                } else if (result != NULL) {
                    *result = 1;
                }
            }
            return 1;
        }
        if (eventType == 0xD2) {
            fn_801261F4(runtime);
            fn_8012B344(runtime);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x6E) {
            fn_80077880(context, actor, event);
            return 1;
        }
        if (eventType == 0xF3) {
            s32 value;
            value = fn_80200C38(event);
            fn_800EA0FC(context, actor, value, event, result);
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
            fn_80095954(context, runtime, owner, actor, event);
            return 1;
        }
    } else if (state == 0x15) {
        if (eventType == 1) {
            fn_8012B344(runtime);
            return 1;
        }
        if (eventType == 3) {
            if (fn_800BE70C(runtime, &actor->target, 2, 0, lbl_8064EC78, lbl_8064ED04, lbl_8064ECAC) == 0) {
                fn_8012B344(runtime);
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 2) {
            s32 anim;
            s32 animFlags;
            anim = fn_80128EAC(runtime);
            animFlags = fn_801290D0(runtime);
            if ((animFlags & 4) && (anim == 3 || anim == 2)) {
                animFlags &= ~4;
                fn_80128F74(runtime, animFlags);
            }
            return 1;
        }
    } else if (state == 3) {
        if (eventType == 3) {
            fn_800BE010(context, actor);
            if (fn_80201C48(handle) != 0) {
                fn_800BDEE4(context, actor);
            }
            fn_80093F6C(context, runtime, owner, actor, event, frame, facing);
            return 1;
        }
        if (eventType == 0x66) {
            fn_8012B344(runtime);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (state == 6) {
        if (eventType == 0xC) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, lbl_8064B5F8, names->tag, lbl_8064B600, names->file) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
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
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0x6B) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
    } else if (state == 0x4A) {
        if (eventType == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xAB) {
            if (fn_801294DC(runtime, 0x90, 0x25, 8) == NULL) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 3) {
            if (fn_800931D0(context, owner, actor) != 0 || fn_80092C30(context, ownerState) != 0) {
                data->owner->timer = 0;
                fn_8020123C(5, owner, owner, 0);
            }
            return 1;
        }
        if (eventType == 5) {
            void *task;
            if ((task = fn_801294DC(runtime, 0x91, 0x24, 8)) != NULL) {
                fn_80128C28(task, fn_80204810, (owner << 8) | 6);
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 2) {
            fn_802006D4(owner, owner, 0x4A, 5, 0);
            return 1;
        }
        if (eventType == 0xAA) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
    } else if (state == 0x20) {
        if (eventType == 5) {
            s32 anim;
            s32 animFlags;
            anim = fn_80128EAC(runtime);
            animFlags = fn_801290D0(runtime);
            if (fn_80128E30(runtime) != NULL && anim == 0xF && (animFlags & 1)) {
                fn_8012B344(runtime);
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneB, lbl_8064B60C, names->tag, lbl_8064B600, names->file) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8020123C(5, owner, owner, 0);
            ownerState->flags &= ~0x200;
            if (lbl_803003C8.mode != 9 || lbl_8064C55C == 0) {
                ownerState->flags &= ~0x800;
            }
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
        if (eventType == 0xAA) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0xAC) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0xAD) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
    } else if (state == 0x4F) {
        if (eventType == 3) {
            EffectData *effect;
            f32 target;
            f32 magnitude;
            effect = fn_800935CC(0, NULL, actor->effect, 4);
            target =fn_80179F20(fn_80179FE4(effect->values, 1, effect->amount));
            temps.angle1 = fn_8012B750(runtime);
            fn_8017A12C(&temps.delta1, (double)temps.angle1, target);
            magnitude = temps.delta1;
            if (magnitude < lbl_8064EC7C) {
                magnitude = -magnitude;
            }
            if (magnitude > lbl_8064ED04) {
                fn_8017A010(&temps.angle1, 0, target, lbl_8064ED08, lbl_8064ED04);
                fn_8012B7A0(runtime, temps.angle1);
            }
            fn_80094DD0(context, runtime, event);
            return 1;
        }
        if (eventType == 5) {
            s32 anim;
            s32 animFlags;
            s32 currentOwner;
            anim = fn_80128EAC(runtime);
            animFlags = fn_801290D0(runtime);
            currentOwner = fn_80201EB8(context);
            if (currentOwner == lbl_8064D18C) {
                if (fn_80128E30(runtime) != NULL && anim == 0x8E && (animFlags & 1)) {
                    animFlags &= ~1;
                    fn_80128F74(runtime, animFlags);
                }
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            } else {
                fn_80201138(5, context, 0x4F, -1, 0, lbl_8064ED0C);
            }
            return 1;
        }
        if (eventType == 6) {
            fn_8020123C(5, owner, owner, 0);
            return 1;
        }
        if (eventType == 7) {
            fn_802006D4(owner, owner, 0x4F, 5, 0);
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
    } else if (state == 5) {
        if (eventType == 3) {
            fn_80095C20(context, runtime, owner, ownerState);
            return 1;
        }
        if (eventType == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xA8) {
            if (fn_801294DC(runtime, 0x2F, 0x25, 6) == NULL) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 2) {
            s32 anim;
            anim = fn_80128EAC(runtime);
            if (anim == 0x2F || anim == 0x9D || anim == 0x2E) {
                DebugBreakpoint();
            }
            ownerState->flags &= ~8;
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
    } else if (state == 0x47) {
        if (eventType == 1) {
            fn_80095FDC(context, runtime, owner, ownerState, 1);
            return 1;
        }
        if (eventType == 3) {
            fn_80096208(context, runtime, owner, ownerState, 0);
            return 1;
        }
        if (eventType == 6) {
            s32 anim;
            anim = fn_80128EAC(runtime);
            if (anim == 0x2F || anim == 0x9D || anim == 0x2E) {
                fn_80201D2C(context, 5);
                fn_80201D14(context, 1);
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 2) {
            fn_8020123C(6, owner, fn_80201B44(), 0);
            ownerState->linked = 0;
            ownerState->flags &= ~2;
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
    } else if (state == 0x3E) {
        if (eventType == 1) {
            fn_8009552C(context, owner, actor);
            actor->hitCount = 0;
            return 1;
        }
        if (eventType == 3) {
            if (fn_8011FAF4(runtime) & 2) {
                fn_8011FABC(runtime, 2, 0);
                actor->hitCount++;
            }
            if (actor->hitCount > 5) {
                fn_80094DD0(context, runtime, event);
                fn_8020123C(0xBA, owner, owner, 0);
            } else {
                fn_80092D90(context, runtime, owner, event, actor);
            }
            return 1;
        }
        if (eventType == 2) {
            actor->hitCount = 0;
            return 1;
        }
    } else if (state == 0x3F) {
        if (eventType == 1) {
            fn_800955A4(context, owner, actor);
            return 1;
        }
        if (eventType == 0xAC) {
            fn_80095774(context, owner, actor, data, event);
            return 1;
        }
        if (eventType == 0xF4) {
            fn_80096710(context, owner, actor, data, event);
            return 1;
        }
        if (eventType == 0xDA) {
            fn_80095654(context, owner, actor, data, event);
            return 1;
        }
        if (eventType == 0xAE) {
            fn_80096690(owner, 0x8D);
            return 1;
        }
        if (eventType == 0xAA) {
            fn_800934A0(context, runtime, event, result);
            return 1;
        }
        if (eventType == 0xB6) {
            fn_80096830(owner, context, runtime, event);
            return 1;
        }
        if (eventType == 3) {
            fn_80094DD0(context, runtime, event);
            fn_800931D0(context, owner, actor);
            fn_80095894(context, runtime, owner, actor);
            return 1;
        }
        if (eventType == 2) {
            fn_80092CCC(context, owner, actor);
            return 1;
        }
    } else if (state == 7) {
        if (eventType == 3) {
            s32 anim;
            anim = fn_80128EAC(runtime);
            if (anim == 0x10 || anim == 0xF) {
                fn_80094DD0(context, runtime, event);
            }
            return 1;
        }
        if (eventType == 0x36) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, lbl_8064B608, names->tag, lbl_8064B600, names->file) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0xA7) {
            s32 anim;
            anim = fn_80128EAC(runtime);
            if ((anim == 0x10 || anim == 0xF) && result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 0x93) {
            s32 anim;
            anim = fn_80128EAC(runtime);
            if ((anim == 0x10 || anim == 0xF) && result != NULL) {
                *result = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
    } else if (state == 0x6D) {
        if (eventType == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xDB) {
            void *task;
            if ((task = fn_801294DC(runtime, 0xA9, 0x25, 6)) != NULL) {
                fn_80128C44(task, fn_80204810, (owner << 8) | 7);
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, names->sceneC, names->tag, lbl_8064B600, names->file) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 3) {
            EffectData *effect;
            void *task;
            s32 anim;
            s32 queued;
            f32 target;
            f32 magnitude;
            effect = fn_800935CC(0, NULL, actor->effect, 4);
            anim = fn_80128EAC(runtime);
            queued = 0;
            target = fn_80179F20(fn_80179FE4(effect->values, 1, effect->amount));
            temps.angle2 = fn_8012B750(runtime);
            fn_8017A12C(&temps.delta2, (double)temps.angle2, target);
            magnitude = temps.delta2;
            if (magnitude < lbl_8064EC7C) {
                magnitude = -magnitude;
            }
            if (magnitude > lbl_8064ED04) {
                fn_8017A010(&temps.angle2, 0, target, lbl_8064ED08, lbl_8064ED04);
                fn_8012B7A0(runtime, temps.angle2);
            }
            if (!(lbl_8064D5A8 & 0x3F) && fn_80092C30(context, ownerState) != 0) {
                fn_8020123C(0xA7, owner, owner, 0);
                queued = 1;
            }
            if (anim == 0xA9) {
                data->owner->timer--;
                if (fn_800931D0(context, owner, actor) != 0 || fn_80092C30(context, ownerState) != 0) {
                    data->owner->timer = 0;
                }
                if (data->owner->timer <= 0 && queued == 0) {
                    if ((task = fn_801294DC(runtime, 0xA8, 0x24, 6)) != NULL) {
                        fn_80128C28(task, fn_80204810, (owner << 8) | 6);
                    } else {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                    }
                }
            }
            fn_80094DD0(context, runtime, event);
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
    } else if (state == 0x64) {
        if (eventType == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xDB) {
            void *task;
            if ((task = fn_801294DC(runtime, 0x93, 0x25, 6)) != NULL) {
                fn_80128C44(task, fn_80204810, (owner << 8) | 7);
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, lbl_8064B614, names->tag, lbl_8064B600, names->file) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 3) {
            EffectData *effect;
            void *task;
            s32 anim;
            s32 queued;
            f32 target;
            f32 magnitude;
            effect = fn_800935CC(0, NULL, actor->effect, 4);
            anim = fn_80128EAC(runtime);
            queued = 0;
            target = fn_80179F20(fn_80179FE4(effect->values, 1, effect->amount));
            temps.angle3 = fn_8012B750(runtime);
            fn_8017A12C(&temps.delta3, (double)temps.angle3, target);
            magnitude = temps.delta3;
            if (magnitude < lbl_8064EC7C) {
                magnitude = -magnitude;
            }
            if (magnitude > lbl_8064ED04) {
                fn_8017A010(&temps.angle3, 0, target, lbl_8064ED08, lbl_8064ED04);
                fn_8012B7A0(runtime, temps.angle3);
            }
            if (!(lbl_8064D5A8 & 0x3F) && fn_80092C30(context, ownerState) != 0) {
                fn_8020123C(0xA7, owner, owner, 0);
                queued = 1;
            }
            if (anim == 0x93) {
                data->owner->timer--;
                if (fn_800931D0(context, owner, actor) != 0 || fn_80092C30(context, ownerState) != 0) {
                    data->owner->timer = 0;
                }
                if (data->owner->timer <= 0 && queued == 0) {
                    if ((task = fn_801294DC(runtime, 0xA4, 0x24, 6)) != NULL) {
                        fn_80128C28(task, fn_80204810, (owner << 8) | 6);
                    } else {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                    }
                }
            }
            fn_80094DD0(context, runtime, event);
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
    } else if (state == 0x65) {
        if (eventType == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0xDB) {
            void *task;
            if ((task = fn_801294DC(runtime, 0x94, 0x25, 6)) != NULL) {
                fn_80128C44(task, fn_80204810, (owner << 8) | 7);
                return 1;
            }
            return 1;
        }
        if (eventType == 7) {
            if (fn_80035FB8(context, names->sceneA, names->sceneD, names->tag, lbl_8064B600, names->file) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 3) {
            void *task;
            if (fn_80128EAC(runtime) == 0x94) {
                data->owner->timer--;
                if (fn_800931D0(context, owner, actor) != 0 || fn_80092C30(context, ownerState) != 0) {
                    data->owner->timer = 0;
                }
                if (data->owner->timer <= 0) {
                    if ((task = fn_801294DC(runtime, 0xA6, 0x24, 6)) != NULL) {
                        fn_80128C28(task, fn_80204810, (owner << 8) | 6);
                    } else {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                    }
                }
            }
            fn_80094DD0(context, runtime, event);
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
    } else if (state == 0x38) {
        if (eventType == 1) {
            return 1;
        }
        if (eventType == 8) {
            fn_8020123C(0x7E, owner, actor->holder, 0);
            fn_80093D20(context, event);
            return 1;
        }
        if (eventType == 0x7E) {
            actor->holder = 0;
            fn_8012B344(runtime);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x39) {
            fn_8020123C(0x7E, owner, actor->holder, 0);
            actor->holder = 0;
            fn_8012B324(runtime);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8020123C(0x39, owner, owner, 0);
            ownerState->flags &= ~0x200;
            if (lbl_803003C8.mode != 9 || lbl_8064C55C == 0) {
                ownerState->flags &= ~0x800;
            }
            return 1;
        }
        if (eventType == 0x80) {
            s32 sound;
            s32 sender;
            s32 recipient;
            void *task;
            sound = fn_801A717C();
            sender = fn_80201B54(context);
            recipient = fn_80201B44();
            fn_801A74A0(sound, fn_800DE354());
            fn_801A74A8(sound, recipient);
            fn_801A7538(sound, 2);
            fn_801A7518(sound, 0x1E);
            fn_8020123C(0x27, fn_800DE354(), recipient, sound);
            fn_801A7228(sound);
            actor->holder = 0;
            if ((task = fn_801294DC(runtime, 0x18, 0x20, 0xA)) != NULL) {
                fn_80128C28(task, fn_80204810, (sender << 8) | 6);
                fn_80128C44(task, fn_80204810, (sender << 8) | 7);
                fn_80201D2C(context, 0x21);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 2) {
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
    } else if (state == 0x21) {
        if (eventType == 1) {
            fn_800BE8D4(owner);
            return 1;
        }
        if (eventType == 6) {
            void *task;
            fn_801AAE68(0xC1, 0x5A, 0, &temps.pos, 2, 2, 0, lbl_8064D18C, lbl_8064ECC4, 0);
            if ((task = fn_801294DC(runtime, 0x29, 0x20, 0xA)) != NULL) {
                fn_80128C28(task, fn_80204810, (owner << 8) | 6);
                fn_80128C44(task, fn_80204810, (owner << 8) | 7);
                actor->flags |= 0x40000;
                fn_8011FA8C(runtime, 0, 0x02000000);
                data->kind = 0x18;
                actor->holder = 0;
                fn_80201DD8(handle, fn_80201B44());
                fn_80201D34(context, 0x2D);
                fn_80201D1C(context, 1);
            }
            return 1;
        }
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 0x93) {
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
        if (eventType == 0xB) {
            return 1;
        }
        if (eventType == 0x27) {
            return 1;
        }
        if (eventType == 0x7D) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
    } else if (state == 0x34) {
        if (eventType == 1) {
            fn_80036DA4(context, fn_80036D5C(context) & ~0x1C0);
            actor->grabCount = 0;
            return 1;
        }
        if (eventType == 0x72) {
            fn_80077E14(context, runtime, event, owner, actor);
            return 1;
        }
        if (eventType == 0x6F) {
            fn_80036DA4(context, fn_80036D5C(context) | 0x40);
            return 1;
        }
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 0x75) {
            fn_80036DA4(context, fn_80036D5C(context) | 0x100);
            fn_80038308(fn_80201814(fn_80201B44()), 1, &temps.count);
            if (temps.count > 5) {
                fn_800CC650(context, 0x2000, -1, temps.count - 5);
            }
            return 1;
        }
        if (eventType == 0x70) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8020123C(0x74, owner, actor->partner, 0);
            fn_8020123C(0x74, owner, owner, 0);
            ownerState->flags &= ~0x200;
            if (lbl_803003C8.mode != 9 || lbl_8064C55C == 0) {
                ownerState->flags &= ~0x800;
            }
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
            void *task;
            s32 value;
            s32 escaped;
            value = fn_80036D5C(context);
            if (actor->hits >= 8 && !(value & 0x100)) {
                escaped = 1;
            } else {
                escaped = 0;
            }
            actor->hits = 0;
            fn_80036DA4(context, fn_80036D5C(context) & ~0x40);
            if (escaped != 0) {
                if ((task = fn_801294DC(runtime, 0x7F, 0x20, 8)) != NULL) {
                    fn_80128C28(task, fn_80204810, (owner << 8) | 0x70);
                } else {
                    fn_80201D2C(context, 1);
                    fn_80201D14(context, 1);
                }
                actor->partner = 0;
            } else if ((task = fn_801294DC(runtime, 0x7E, 0x20, 8)) != NULL) {
                fn_80128C44(task, fn_80204810, (owner << 8) | 0x71);
                fn_80128C28(task, fn_80204810, (owner << 8) | 0x71);
                fn_80201D2C(context, 0x35);
                fn_80201D14(context, 1);
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
        if (eventType == 0xE6) {
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
                actor->grabCount++;
                if (actor->grabCount > 6) {
                    fn_80128BE4(runtime);
                }
            }
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0xAA) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
    } else if (state == 0x35) {
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 0x71) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8020123C(0x74, owner, owner, 0);
            ownerState->flags &= ~0x200;
            if (lbl_803003C8.mode != 9 || lbl_8064C55C == 0) {
                ownerState->flags &= ~0x800;
            }
            return 1;
        }
        if (eventType == 3) {
            s32 value;
            value = fn_80036D5C(context);
            if (!(lbl_8064D5A8 & 7) && !(value & 0x80)) {
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
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0xE6) {
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0xAA) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
    } else if (state == 0x37) {
        if (eventType == 1) {
            fn_800CA2C8(context);
            fn_801A977C(runtime, 0xA);
            return 1;
        }
        if (eventType == 0xA9) {
            fn_8007791C(context);
            fn_800CC860(context, 3, 0xF);
            fn_800BE8D4(owner);
            fn_8020123C(0x77, owner, owner, 0);
            return 1;
        }
        if (eventType == 0x77) {
            fn_800389E0(context, 0, 0, 1);
            fn_8020104C(0x39, owner, owner, 0, lbl_8064ED10);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            return 1;
        }
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 0x20) {
            return 1;
        }
        if (eventType == 0xE6) {
            return 1;
        }
        if (eventType == 0x35) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0xAA) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0x32) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
    } else if (state == 8) {
        if (eventType == 1) {
            fn_8011FADC(runtime, fn_8011FAEC(runtime) & ~0xC0);
            fn_800CA2C8(context);
            fn_80204FDC(context);
            return 1;
        }
        if (eventType == 3) {
            fn_8003E5DC(context, runtime, owner, actor);
            return 1;
        }
        if (eventType == 0xD2) {
            return 1;
        }
        if (eventType == 0x3D) {
            fn_800BD2DC(context, actor);
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (eventType == 0x11) {
            s32 value;
            fn_800EA3A0(context, actor);
            fn_801294DC(runtime, 0x28, 0x25, 0xA);
            fn_8012C62C(runtime, 0xF,
                PrepareColor(&temps.finalC, &lbl_8064ECF8),
                PrepareColor(&temps.finalB, &lbl_8064ECFC),
                PrepareColor(&temps.finalA, &lbl_806519E0), 4);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            return 1;
        }
        if (eventType == 2) {
            fn_802006D4(owner, owner, 8, 0x11, 0);
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
        if (eventType == 0xB) {
            return 1;
        }
        if (eventType == 0x27) {
            return 1;
        }
        if (eventType == 0x7D) {
            return 1;
        }
        if (eventType == 0xB6) {
            return 1;
        }
        if (eventType == 0xBA) {
            return 1;
        }
        if (eventType == 0x67) {
            return 1;
        }
        if (eventType == 0xA7) {
            return 1;
        }
        if (eventType == 0xF4) {
            return 1;
        }
        if (eventType == 0x93) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
