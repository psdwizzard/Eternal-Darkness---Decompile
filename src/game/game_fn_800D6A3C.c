typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
#define NULL 0

typedef struct GameObject GameObject;
typedef struct Event Event;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Actor Actor;
typedef struct ActorVtable {
    void (*unk0)(Actor *, void *);
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void *);
    void (*unk14)(Actor *, void *, void *);
    void (*unk18)(Actor *, void *, void *);
    void (*unk1C)(Actor *, void *, void *);
    void (*unk20)(Actor *, void *, void *);
    void (*unk24)(Actor *, void *, void *);
} ActorVtable;
typedef struct ActorSounds {
    u16 unk0;
    u8 pad02[0xE];
    u16 unk10;
} ActorSounds;
struct Actor {
    ActorVtable *unk0;
    u8 pad04[0x64];
    int unk68;
    u8 pad6C[0xC];
    Vec3 unk78;
    u16 unk84;
    u16 unk86;
    Vec3 unk88;
    u8 pad94[0xFC];
    int unk190;
    u8 pad194[4];
    int unk198;
    u8 pad19C[0xC4];
    u16 unk260;
    u16 pad262;
    ActorSounds *unk264;
    u8 pad268[0xC];
    u8 unk274[0xC];
    u8 unk280;
    u8 pad281;
    s8 unk282;
    s8 unk283;
    s16 unk284;
    u8 pad286;
    u8 unk287;
    u8 pad288[0x10];
    u32 unk298;
    u16 unk29C;
    u8 pad29E[4];
    u8 flag7 : 1;
    u8 flag6 : 1;
    u8 flag5 : 1;
    u8 flag4 : 1;
    u8 flag3 : 1;
    u8 flag2 : 1;
    u8 flag1 : 1;
    u8 flag0 : 1;
};
typedef struct Context {
    u8 pad00[0x64];
    Actor *unk64;
    u8 pad68[0x24];
    u8 *unk8C;
    u8 pad90[4];
    void *unk94;
} Context;
typedef struct EventData {
    u8 pad00[0x20];
    int id;
} EventData;

extern unsigned char lbl_80248B78[];
extern unsigned char lbl_8064B770[8];
extern unsigned char lbl_8064B778[8];
extern unsigned char lbl_8064B780[8];
extern int lbl_8064D180;
extern int lbl_8064D5A8;
extern unsigned int lbl_8064F3F8;
extern unsigned int lbl_8064F3FC;
extern float lbl_8064F400;
extern float lbl_8064F404;
extern float lbl_8064F408;
extern unsigned int lbl_80651AB8;
extern void fn_80008B38();
extern void fn_80008C8C();
extern void fn_80008CA0();
extern s32 fn_800359A0();
extern int fn_80038308();
extern void fn_80045A24();
extern s32 fn_800460EC();
extern void fn_80064B38();
extern s32 fn_800654F8();
extern u8 fn_800A1AE0();
extern int fn_800A1DA0();
extern int fn_800A200C();
extern int fn_800A2018();
extern int fn_800A2060();
extern int fn_800A20C0();
extern void fn_800A2414();
extern void fn_800A2430();
extern int fn_800A24A4();
extern void fn_800A2598();
extern void fn_800A25D8();
extern int fn_800A2688();
extern int fn_800A270C();
extern s32 fn_800A2798();
extern int fn_800A2A80();
extern int fn_800A2B80();
extern void fn_800A2B8C();
extern void fn_800A2D1C();
extern void fn_800A2DC8();
extern void fn_800A2E00();
extern void fn_800A2ED8();
extern void fn_800A2F0C();
extern void fn_800A2F7C();
extern u8 fn_800A306C(Actor *);
extern int fn_800A3074();
extern int fn_800A30AC();
extern void fn_800A30B8();
extern u8 fn_800A30F4();
extern int fn_800A3104();
extern int fn_800A3180();
extern void fn_800A3274();
extern void fn_800A357C();
extern int fn_800A3588();
extern int fn_800A383C();
extern void fn_800A3894();
extern void fn_800A397C();
extern int fn_800A3A10();
extern void fn_800A3AC4();
extern void fn_800A3AF8();
extern void fn_800A3C2C();
extern void fn_800A3C4C();
extern void fn_800A3D90();
extern void fn_800A40C4();
extern int fn_800A4428();
extern int fn_800A44D4();
extern void fn_800A4634();
extern void fn_800A4798();
extern void fn_800A4978();
extern void fn_800BE8D4();
extern int fn_800CA2C8();
extern void fn_800CC4DC();
extern void fn_800CC860();
extern void fn_800CD094();
extern void fn_800D6974();
extern void fn_800D86E8();
extern void fn_800D87B4();
extern void fn_800D8828();
extern void fn_800D8EC4();
extern void fn_800D9C48();
extern int fn_800D9D64();
extern int fn_800DA110();
extern int fn_800DA1D4();
extern void fn_800DA278();
extern int fn_800DA400();
extern void fn_8011F114(Vec3 *, void *);
extern unsigned int fn_8011FA8C();
extern void * fn_8011FE54();
extern void fn_801287C4();
extern void fn_8012880C();
extern void * fn_80128E30();
extern void * fn_8012965C();
extern int fn_801296F8();
extern void fn_8012B324();
extern void fn_8012B344();
extern void * fn_8012C62C();
extern u8 fn_8013017C();
extern int fn_801301B0();
extern int fn_801305D4();
extern void fn_801A7228();
extern u32 fn_801A7498();
extern u32 fn_801A74C0();
extern u32 fn_801A7570();
extern void fn_801A7588();
extern u32 fn_801A7590();
extern void fn_801A9DCC();
extern int fn_801AC9F4(u16, u8, Vec3 *, u8);
extern int fn_801E8328();
extern int fn_802006D4();
extern int fn_80200C10();
extern int fn_80200C20();
extern int fn_80200C28();
extern void * fn_80200C38();
extern void fn_8020104C(int, int, int, int, float);
extern void fn_802010C8(int, void *, int, float);
extern u64 fn_8020123C(int, int, int, int);
extern void * fn_80201814();
extern void * fn_80201B3C();
extern int fn_80201B44();
extern int fn_80201B54();
extern void * fn_80201B94();
extern void * fn_80201BC8();
extern void fn_80201D14();
extern void fn_80201D1C();
extern void fn_80201D2C();
extern void fn_80201D34();
extern void fn_80201DD8();
extern void fn_80201E78();
extern void fn_802020B4();
extern void fn_80204FDC();
extern void *fn_80201B8C();
extern int fn_800A1A84();

/* Dispatch actor events for the current behavior state. */
int fn_800D6A3C(GameObject *object, int state, Event *event, int *result) {
    s32 senderId;
    u16 failedAttempts;
    Vec3 position;
    Vec3 targetPosition;
    Vec3 soundPosition;
    Vec3 fetchedPosition;
    unsigned int effectStart;
    unsigned int effectEnd;
    unsigned int effectColor;
    short channel;
    u16 cancelFlags;
    s32 eventId;
    s32 targetObjectId;
    u8 volume;
    s32 menuState;
    Context *objectContext;
    void *queue;
    unsigned char *definition;
    s32 itemResult;
    u16 soundId;
    u16 interruptFlags;
    s32 objectId;
    Actor *actor;
    unsigned char *strings = lbl_80248B78;
    void *relation;
    void *target;
    s32 kind;
    s32 menuChoice;
    void *runtime;
    Context *context;
    s32 targetId;
    void *item;

    kind = fn_80200C10(event);
    target = fn_80201B3C();
    if (target != 0) {
        targetObjectId = fn_80201B54(target);
    } else {
        targetObjectId = -1;
    }
    senderId = fn_80200C20(event);
    runtime = fn_80201BC8(object);
    objectContext = fn_80201B8C(object);
    context = objectContext;
    definition = context->unk8C;
    actor = context->unk64;
    relation = fn_80201B94(object);
    objectId = fn_80201B54(object);
    fn_8011F114(&position, runtime);
    targetId = fn_80201B44();
    fn_80201DD8(relation, targetId);
    if (kind == 3) {
        int create;
        int hit = 0;
        create = actor->unk86 != 2;
        fn_800CC4DC(object);
        hit |= fn_800A3588(actor, object, &actor->unk88, target, create);
        if (hit) {
            fn_801AC9F4(actor->unk264->unk0, 0x64, &position, 2);
        }
        actor->unk0->unk10(object);
        if ((fn_8013017C(runtime) & 0x40) && (fn_801305D4(runtime) == 0)) {
            fn_801301B0(runtime, 0x40, 0);
        }
        if (!(lbl_8064D5A8 & 0xF)) {
            fn_80201E78(&fetchedPosition, target);
            targetPosition = fetchedPosition;
            fn_800A3894(actor, &position, &targetPosition);
        }
    }
    if (state == 0x0) {
        if (kind == 0x1) {
            fn_800359A0(object, 0);
            fn_80201DD8(relation, 0);
            fn_800A3104(actor, 0);
            fn_800A3AC4(actor);
            actor->unk0->unk0(actor, object);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x8) {
            fn_800A2598(actor);
            fn_800A3274(actor, object, 3);
            actor->unk0->unk20(actor, object, event);
            fn_8020123C(0xFC, objectId, targetObjectId, 0U);
            fn_800A2D1C(actor);
            fn_800CD094(object, event, 0xB4);
            return 1;
        } else if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (kind == 0x3E) {
            if ((u8) actor->unk287 == 0) {
                actor->unk287 = 1U;
                fn_800A2B8C(object, fn_800A2018(actor, actor->unk86));
                fn_800A2E00(actor, objectId, 0x319);
            } else if (!actor->flag7 && ((s32) lbl_8064D180 == 0x53)) {
                actor->unk284 = 0xD2;
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 0xB) {
            itemResult = 0;
            item = fn_80200C38(event);
            if (fn_800A3A10(actor, definition + 0xEA, item) != 0) {
                if (((fn_801A74C0(item) >> 0x10U) & 1) && (fn_801A7590(item) & 0x8000)) {
                    fn_800A4798(object, item);
                    fn_801A7588(item, 1 << actor->unk198);
                }
                fn_800A4634(actor, runtime);
                itemResult = fn_800654F8(item);
                fn_8020123C(0x97, objectId, objectId, actor->unk264->unk10);
            } else {
                failedAttempts = actor->unk29C;
                actor->unk29C = (u16) (failedAttempts + 1);
                if (fn_801A7570(item) & 0x10018) {
                    if (((u16) actor->unk29C == 1) || actor->flag4) {
                        fn_8020104C(0x97, objectId, objectId, 0x2B5, lbl_8064F400);
                        fn_80201D2C(object, 0x7E);
                        fn_80201D14(object, 1);
                    } else {
                        fn_800A383C(actor);
                        fn_8020104C(0x97, objectId, objectId, 0x2B5, lbl_8064F400);
                        fn_800A40C4(runtime, actor, context->unk94, item);
                    }
                } else {
                    int itemOwner = fn_801A7498(item);
                    if (itemOwner != 0) {
                        if (fn_80201BC8(fn_80201814(itemOwner)) != 0) {
                            fn_80201DD8(relation, itemOwner);
                        }
                    }
                }
            }
            if (result != NULL) {
                *result = itemResult;
            }
            return 1;
        } else if (kind == 0xDC) {
            fn_800A2430(actor, 5, event, result);
            return 1;
        } else if (kind == 0x27) {
            fn_80064B38(object, event, result);
            return 1;
        } else if (kind == 0x3D) {
            fn_800D8828(actor, object, event);
            return 1;
        } else if (kind == 0x97) {
            soundId = (u16)fn_80200C38(event);
            volume = 0x64;
            soundPosition = position;
            switch ((s32) soundId) {
            case 0x2B5:
            case 0x13A:
                soundId = 0x2B5;
                fn_80201E78(&soundPosition, target);
                /* fallthrough */
            case 0x243:
                volume = 0x7F;
                break;
            }
            fn_801AC9F4(soundId, volume, &soundPosition, 2);
            return 1;
        } else if (kind == 0x20) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0x6B) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0x3B) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        } else if (kind == 0x82) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0xE6) {
            if (fn_800A30AC(actor) != 0) {
                fn_800A3D90(object, runtime, event, result);
            }
            return 1;
        } else if (kind == 0x35) {
            if (fn_800A30AC(actor) != 0) {
                fn_800A3D90(object, runtime, event, result);
            }
            return 1;
        } else if (kind == 0x39) {
            fn_8012B324(runtime);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        } else if (kind == 0x91) {
            fn_800A3C2C(actor, senderId);
            return 1;
        } else if (kind == 0xF6) {
            void *data = fn_80200C38(event);
            fn_800D86E8(actor, senderId, data);
            return 1;
        } else if (kind == 0xF8) {
            fn_800A2414(actor, event);
            return 1;
        } else if (kind == 0xFA) {
            fn_80200C38(event);
            actor->flag6 = 0;
            fn_800A2F0C(actor, 1);
            return 1;
        } else if (kind == 0xE0) {
            fn_801296F8(runtime, 0x9911);
            fn_800A3104(actor, 1);
            fn_800A3AC4(actor);
            fn_800A2688(runtime, object);
            fn_800D9C48(object, &actor->unk78);
            return 1;
        } else if (kind == 0x1C) {
            if (fn_800460EC() == 0) {
                actor->flag7 = (unsigned int)fn_80200C38(event);
            }
            return 1;
        } else if (kind == 0x37) {
            return 1;
        } else if (kind == 0x32) {
            return 1;
        } else if (kind == 0x1E) {
            return 1;
        }
    } else if (state == 0x1) {
        if (kind == 1) {
            return 1;
        } else if (kind == 2) {
            return 1;
        } else if (kind == 3) {
            if (actor->flag1) {
                actor->flag1 = 0;
                fn_800A3AF8(object);
            }
            fn_800A1DA0(actor, 0xE5);
            if ((targetId != 0) && (actor->unk284 == 0)) {
                int handled = 0;
                if ((u16) actor->unk86 == 2) {
                    if (actor->unk283 <= 0) {
                        fn_800A2F7C(actor);
                    }
                    handled = fn_800A2798(object, runtime, event, 0);
                    if (handled != 0) {
                        fn_80201D2C(object, 0x71);
                        fn_80201D14(object, 1);
                    }
                } else if ((fn_800460EC() == 0) && (fn_800A3180(object, &position) != 0)) {
                    int special = actor->unk86 == 2;
                    if (special == 0) {
                        fn_800A270C(object, runtime, 0);
                    }
                    handled = fn_800A2798(object, runtime, event, special);
                    if (handled != 0) {
                        fn_80201D2C(object, 6);
                        fn_80201D14(object, 1);
                    }
                } else {
                    u16 actorType = actor->unk86;
                    if (actorType == 0) {
                        handled = fn_800A24A4(object, runtime, actor, event);
                        if (handled != 0) {
                            fn_80201D2C(object, 0x42);
                            fn_80201D14(object, 1);
                        }
                    } else if (actorType == 1) {
                        handled = fn_800DA400(object, runtime, event);
                        if (handled != 0) {
                            fn_80201D2C(object, 0x70);
                            fn_80201D14(object, 1);
                        }
                    }
                }
                if (handled == 0) {
                    fn_800A25D8(object, runtime);
                }
            }
            if (!(lbl_8064D5A8 & 7)) {
                fn_80201DD8(relation, fn_80201B44());
            }
            return 1;
        }
    } else if (state == 0x61) {
        if (kind == 1) {
            return 1;
        } else if (kind == 3) {
            fn_800A25D8(object, runtime);
            return 1;
        } else if (kind == 7) {
            fn_800A270C(object, runtime, 0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 12) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 2) {
            fn_800A357C(actor);
            return 1;
        }
    } else if (state == 0x6) {
        if (kind == 3) {
            fn_800A1DA0(actor, 0xE5);
            if (((u8) actor->unk280 != 0) && !(lbl_8064D5A8 & 3)) {
                fn_800A25D8(object, runtime);
            }
            return 1;
        } else if (kind == 12) {
            fn_800A1AE0(&actor->unk274, 0);
            actor->unk0->unk18(actor, object, event);
            if ((u16) actor->unk86 == 2) {
                fn_80038308(object, 0, &channel);
                fn_800A4428(object, channel);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 7) {
            fn_800A1AE0(&actor->unk274, 0);
            fn_800A270C(object, runtime, 0);
            actor->unk0->unk1C(actor, object, event);
            if (fn_800A2A80(object, strings + 0x50, lbl_8064B770, strings + 0x64, lbl_8064B778, strings + 0x70) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 13) {
            fn_800A1AE0(&actor->unk274, 0);
            fn_800A270C(object, runtime, 0);
            actor->unk0->unk14(actor, object, event);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(runtime);
            return 1;
        } else if (kind == 2) {
            fn_800A3AC4(actor);
            return 1;
        }
    } else if (state == 0x71) {
        if (kind == 1) {
            fn_800A30F4(actor, 1);
            return 1;
        } else if (kind == 2) {
            return 1;
        } else if (kind == 3) {
            fn_800A1DA0(actor, 0xE5);
            if (actor->unk284 > 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (((u8) actor->unk280 != 0) && !(lbl_8064D5A8 & 7)) {
                fn_800A25D8(object, runtime);
            }
            return 1;
        } else if (kind == 12) {
            actor->unk283 = (u8) (actor->unk283 - 1);
            if (actor->unk283 > 0) {
                if (fn_800A2798(object, runtime, event, 0) == 0) {
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            } else if (fn_800DA1D4(object) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 7) {
            actor->unk284 = 0xD2;
            fn_800A270C(object, runtime, 0);
            fn_800D87B4(actor, object, event);
            fn_800A2A80(object, strings + 0x50, lbl_8064B780, strings + 0x64, lbl_8064B778, strings + 0x70);
            return 1;
        }
    } else if (state == 0x42) {
        if (kind == 0x1) {
            actor->unk84 = (u16) (actor->unk84 & ~0x410);
            return 1;
        } else if (kind == 0x3) {
            fn_800A1DA0(actor, 0xE5);
            return 1;
        } else if (kind == 0xC) {
            fn_800A1AE0(&actor->unk274, 0);
            if (actor->unk84 & 0x10) {
                u64 eventResult = fn_8020123C(0x99, objectId, targetId, 1);
                actor->unk84 = (u16) (actor->unk84 & 0xFFFFFFEF);
                if ((u32)(eventResult & 0xFFFFFFFF)) {
                    fn_80201D2C(object, 0x43);
                    fn_80201D14(object, 1);
                } else {
                    fn_800DA278(actor, 0);
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            } else {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 0x7) {
            fn_800A1AE0(&actor->unk274, 0);
            fn_800A270C(object, runtime, 0);
            cancelFlags = actor->unk84;
            if (cancelFlags & 0x10) {
                fn_800DA278(actor, 1);
                actor->unk84 = (u16) (actor->unk84 & 0xFFFFFFEF);
            } else if (cancelFlags & 0x400) {
                fn_800D9D64(runtime, object);
                actor->unk84 = (u16) (actor->unk84 & 0xFFFFFBFF);
            }
            if (fn_800A2A80(object, strings + 0x88, lbl_8064B770, strings + 0x64, lbl_8064B778, strings + 0x70) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 0x98) {
            fn_8020123C(0xD, objectId, objectId, 0U);
            return 1;
        } else if (kind == 0xD) {
            fn_800A1AE0(&actor->unk274, 0);
            fn_800A270C(object, runtime, 0);
            interruptFlags = actor->unk84;
            if (interruptFlags & 0x10) {
                fn_800DA278(actor, 0);
                actor->unk84 = (u16) (actor->unk84 & 0xFFFFFFEF);
            } else if (interruptFlags & 0x400) {
                fn_800D9D64(runtime, object);
                actor->unk84 = (u16) (actor->unk84 & 0xFFFFFBFF);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8012B344(runtime);
            return 1;
        } else if (kind == 0x2) {
            return 1;
        }
    } else if (state == 0x43) {
        if (kind == 0x98) {
            fn_800DA278(actor, 0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
    } else if (state == 0x7) {
        if (kind == 0x1) {
            if ((u16) actor->unk86 == 2) {
                fn_800A2598(actor);
            }
            fn_800A3104(actor, 0);
            fn_800A3C4C(runtime, context, 0, 0);
            fn_800A2DC8(actor);
            return 1;
        } else if (kind == 0x36) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x7) {
            fn_800A270C(object, runtime, 0);
            if (fn_800A2A80(object, strings + 0x50, lbl_8064B780, strings + 0x64, lbl_8064B778, strings + 0x70) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 0x2) {
            actor->flag1 = 1;
            fn_800A4978(object, runtime, context);
            if (fn_800A2A80(object, strings + 0x50, lbl_8064B780, strings + 0x64, lbl_8064B778, strings + 0x70) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            actor->unk190 = -1;
            return 1;
        }
    } else if (state == 0x70) {
        if (kind == 0x1) {
            fn_800A30B8(actor, 1);
            return 1;
        } else if (kind == 0x2) {
            return 1;
        } else if (kind == 0x3) {
            fn_800A1DA0(actor, 0xE5);
            if (actor->unk282 == 0) {
                if (fn_800A306C(actor) != 0) {
                    fn_8020104C(0xD3, objectId, objectId, 0, lbl_8064F404);
                    fn_80201D2C(object, 0x6E);
                    fn_80201D14(object, 1);
                } else {
                    fn_80201D2C(object, 0x6F);
                    fn_80201D14(object, 1);
                }
            } else if ((fn_800A44D4(actor) == 0) && (fn_800A200C(actor) == 0)) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if ((fn_800A200C(actor) == 0) && (fn_800A3074(targetId) == 0x32)) {
                fn_80201D2C(object, 0x6F);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 0x78) {
            eventId = ((EventData *)fn_80200C38(event))->id;
            actor->unk0->unk24(actor, object, event);
            fn_800A397C(actor, object, runtime);
            fn_8020123C(0xD5, objectId, eventId, objectId);
            return 1;
        } else if (kind == 0x7) {
            if (fn_800A2A80(object, strings + 0x50, lbl_8064B780, strings + 0x64, lbl_8064B778, strings + 0x70) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (state == 0x8) {
        if (kind == 0x1) {
            if (runtime != 0U) {
                fn_8011FA8C(runtime, 0xC0, 0);
            }
            fn_800CC860(object, 1, 0);
            fn_800BE8D4(objectId);
            fn_800CA2C8(object);
            fn_80204FDC(object);
            return 1;
        } else if (kind == 0x11) {
            effectColor = lbl_80651AB8;
            effectEnd = lbl_8064F3FC;
            effectStart = lbl_8064F3F8;
            fn_8012C62C(runtime, 0xF, &effectStart, &effectEnd, &effectColor, 4);
            fn_80201D34(object, 0x15);
            fn_80201D1C(object, 1);
            return 1;
        } else if (kind == 0x2) {
            fn_802006D4(objectId, objectId, 8, 0x11, 0);
            return 1;
        } else if (kind == 0xEF) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        } else if (kind == 0x3D) {
            fn_8020123C(0x39, objectId, objectId, 0U);
            return 1;
        } else if (kind == 0x3B) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0x35) {
            return 1;
        } else if (kind == 0x8) {
            return 1;
        } else if (kind == 0xB) {
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 0x37) {
            return 1;
        } else if (kind == 0x1E) {
            return 1;
        } else if (kind == 0x32) {
            return 1;
        }
    } else if (state == 0x73) {
        if (kind == 1) {
            fn_802010C8(6, object, 0, lbl_8064F408);
            return 1;
        } else if (kind == 2) {
            fn_8012B344(runtime);
            return 1;
        } else if (kind == 3) {
            fn_800A1DA0(actor, 0xE5);
            return 1;
        } else if (kind == 6) {
            if (fn_800DA110(object) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 7) {
            if (fn_800A2A80(object, strings + 0x50, lbl_8064B780, strings + 0x64, lbl_8064B778, strings + 0x70) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (state == 0x56) {
        if (kind == 0x1) {
            fn_800A3104(actor, 1);
            fn_800A3AC4(actor);
            fn_800A2688(runtime, object);
            fn_8020104C(0xD4, objectId, objectId, 0, (f32) actor->unk260);
            return 1;
        } else if (kind == 0x3) {
            fn_800A1DA0(actor, 0xE5);
            return 1;
        } else if (kind == 0xD4) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x2) {
            fn_800A270C(object, runtime, 0);
            fn_800A3104(actor, 0);
            fn_800D8EC4(actor, runtime, 1);
            return 1;
        } else if (kind == 0x78) {
            actor->unk68 = 0;
            fn_800D8EC4(actor, runtime, 1);
            return 1;
        } else if (kind == 0x7) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
    } else if (state == 0x6E) {
        if (kind == 0x1) {
            return 1;
        } else if (kind == 0x2) {
            fn_800A3104(actor, 0);
            fn_800A270C(object, runtime, 0);
            return 1;
        } else if (kind == 0xD3) {
            fn_800A2688(runtime, object);
            fn_8020104C(0xD4, objectId, objectId, 0, (f32) actor->unk260);
            return 1;
        } else if (kind == 0xD4) {
            if (fn_800A2B80(actor) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else {
                fn_80201D2C(object, 0x6F);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 0x3) {
            fn_800A25D8(object, runtime);
            fn_800A1DA0(actor, 0xE5);
            return 1;
        }
    } else if (state == 0x6F) {
        if (kind == 1) {
            fn_800A270C(object, runtime, 0);
            return 1;
        } else if (kind == 2) {
            fn_800A3104(actor, 0);
            return 1;
        } else if (kind == 3) {
            fn_800A1DA0(actor, 0xE5);
            if (fn_800A2B80(actor) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if ((fn_800460EC() == 0) && (fn_800A3180(object, &position) != 0) && (actor->unk284 == 0)) {
                fn_800A2798(object, runtime, event, 0);
            }
            return 1;
        }
    } else if (state == 0x7E) {
        if (kind == 1) {
            actor->flag4 = 0;
            actor->flag3 = 0;
            actor->unk298 = 0U;
            fn_800A270C(object, runtime, 0);
            fn_800D6974(actor, object);
            fn_800A2DC8(actor);
            queue = fn_8012965C(runtime, (int)fn_8011FE54(runtime), 0x21, 1);
            if (queue != 0) {
                fn_801287C4(queue, fn_800A1A84, (unsigned int)actor, 0x23);
                fn_802020B4(object, 0);
                fn_80045A24(1, 0);
            } else {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (kind == 2) {
            queue = fn_80128E30(runtime);
            if (queue != 0) {
                fn_8012880C(queue, 0, 0);
            }
            actor->flag3 = 0;
            fn_800A2ED8(actor, 1);
            fn_80045A24(0, 0);
            fn_802020B4(object, 1);
            fn_801A9DCC(0, 0x64, 0x1E);
            return 1;
        } else if (kind == 3) {
            if (actor->flag3) {
                menuChoice = fn_800A2060(actor);
                menuState = fn_800A20C0(actor);
                switch (menuState) {
                case 1:
                    break;
                case 2:
                    if (actor->unk298 == 0) {
                        switch (menuChoice) {
                        case 0:
                            fn_80008B38(strings + 0x20, 2, 2);
                            fn_80008C8C();
                            break;
                        case 1:
                        default:
                            fn_80008B38(strings + 0x30, 2, 4);
                            fn_80008C8C();
                            break;
                        }
                        actor->unk298 = 1;
                    }
                    break;
                case 0:
                    fn_80008CA0();
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                    break;
                }
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
