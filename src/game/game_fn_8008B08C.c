/* Trapper AI state/event dispatcher. */

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
#define NULL 0

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ActionState {
    int owner;
    u8 status;
    u8 pad05[3];
    s16 searchTimer;
    s16 blockedCount;
    u8 timer, delay, cancelled;
} ActionState;

typedef struct ActorState {
    u32 flags;
    u8 pad04[0x90];
    Vec3 position;
    u8 padA0[0xAE];
    s16 cooldown;
    s16 delay;
    u8 pad152[0xF];
    s8 mask;
    u8 pad162[5];
    u8 attempts;
} ActorState;

typedef struct ObjectInfo {
    u8 pad00[0x48];
    ActionState* action;
    u8 pad4C[0x40];
    ActorState* actor;
    void* field90;
    int kind;
    u8 pad98[4];
    s16 flagOffset;
    u8 field9E;
    u8 type;
} ObjectInfo;

extern int fn_800359A0(void*, void*);
extern int fn_80035FB8();
extern void* fn_80036D5C(void*);
extern void fn_80036DA4(void*, void*);
extern int fn_8003BF5C(void*);
extern int fn_8003C04C(void*);
extern void fn_8003C114(void*, void*, int);
extern int fn_800462C8(int);
extern int fn_80049220(void*, int);
extern int fn_80049304(void*, int);
extern void fn_8005FF94();
extern void fn_80064B38(int, void*, int*);
extern int fn_800654F8(int);
extern void fn_800674E4(int, int);
extern void fn_80067650();
extern void fn_8008A6F8();
extern void fn_8008A914(void*, u32, void*);
extern int fn_8008A96C(void*, void*, void*);
extern int fn_8008ABCC();
extern int fn_8008ABD4(void*, void*, int, int);
extern int fn_8008AF24(void*, void*, void*, u32, u32);
extern int fn_8008C7F8(ActionState*, void*, Vec3*, int, void*);
extern int fn_8008C93C(void*, void*);
extern u8 fn_8008C9AC(void*);
extern u8 fn_8008C9BC(ActionState*, ObjectInfo*);
extern void fn_8008CA70(void*);
extern void fn_8008CA84(void*);
extern void fn_8008CAD4(int, void*, int, int);
extern void fn_8008CBA4(void*);
extern void fn_8008CBB8(void*);
extern void fn_8008CBD4(void*);
extern u32 fn_8008CBE8(void*, u32);
extern void fn_8008CC20(void*);
extern void fn_8008CC50(void*);
extern int fn_8009A2B8(void*, void*, void*, void*, void*, void*, u32, int, float);
extern const short** fn_800BC100(int, Vec3*, int*, int, int*, int*, int);
extern void fn_800BCCC4(const short*, Vec3*);
extern void fn_800BD194(void*, void*);
extern void fn_800BD2DC(void*, void*);
extern void fn_800BDEE4(void*, void*);
extern void fn_800BE010(void*, void*);
extern int fn_800BE86C(void*, Vec3*, int, int, float);
extern void fn_800BE8D4(int);
extern void fn_800C9E50(void*);
extern int fn_800CA1BC(void*, void*, void*, int*);
extern int fn_800CA2C8(void*);
extern float fn_800CB444(void*, void*);
extern void fn_800CC4DC(void*);
extern void fn_800CC860(void*, int, int);
extern void fn_800CCC78(void*, int);
extern void fn_800CF598(void*);
extern void fn_800EA0FC(void*, void*, int, void*, int*);
extern void fn_800EA3A0(void*, void*);
extern u32 fn_800FBFB0(void);
extern void fn_8011F0E8(void*, Vec3*);
extern void fn_8011F104(void*, float, float, float);
extern void fn_8011F114(Vec3*, void*);
extern float fn_8011F778(void*, float);
extern u32 fn_8011FA8C(void*, u32, u32);
extern u32 fn_8011FABC(void*, u32, u32);
extern u32 fn_8011FAEC(void*);
extern u32 fn_8011FAF4(void*);
extern void* fn_8011FB4C(void*);
extern int fn_8011FF38(void);
extern void fn_80120AD0(void*, void*, u16, u32, float, float);
extern void fn_801261F4(void*);
extern int fn_80128EAC(void*);
extern void fn_80128F74(void*, u32);
extern u16 fn_801290D0(void*);
extern void* fn_801294DC(void*, int, int, int);
extern void* fn_8012976C(void*, int, int, Vec3*, float);
extern int fn_80129928(void*, Vec3*);
extern int fn_8012AFC4(void*);
extern void fn_8012B324(void*);
extern void fn_8012B344(void*);
extern void* fn_8012C62C(void*, int, void*, void*, void*, int);
extern u16 fn_8012DBE8(void*, u32, u8*);
extern void fn_8013B83C(void*);
extern int fn_80179064(int, int, int, int);
extern void fn_801A7228(void*);
extern u32 fn_801A74C0(void*);
extern void fn_801A7588(void*, u32);
extern int fn_801AAE68(u16, u8, u8, float, Vec3*, s8, u8, u8, u16, u32);
extern void fn_801D14CC(int);
extern int fn_801E8328(u32, u32);
extern int fn_802006D4(int, int, int, int, void*);
extern int fn_80200C10(void*);
extern int fn_80200C20(void*);
extern int fn_80200C28(void*);
extern void* fn_80200C38(void*);
extern void fn_8020104C(int, int, int, int, float);
extern u64 fn_8020123C(int, int, int, int);
extern void* fn_80201814(int);
extern void* fn_80201B3C(void);
extern int fn_80201B44(void);
extern int fn_80201B54(void*);
extern int fn_80201B5C(void*);
extern void* fn_80201B8C(void*);
extern void* fn_80201B94(void*);
extern void* fn_80201BC8(void*);
extern void* fn_80201C48(void*);
extern u32 fn_80201CD4(void*);
extern void fn_80201D14(void*, u8);
extern void fn_80201D1C(void*, u8);
extern void fn_80201D2C(void*, int);
extern void fn_80201D34(void*, int);
extern void fn_80201DD8(void*, void*);
extern void fn_80201E60(void*, int);
extern void fn_80201F44(void*, Vec3*);
extern u8 fn_80204578(void*, const Vec3*);
extern int fn_802045AC(void*, Vec3*);
extern void fn_80204FDC(void*);

typedef struct TextTable {
    char name[0x14];
    char interrupted[0xC];
    char idleMessage[0x18];
    char finishingResponse[0x14];
    char assertion[0xC];
} TextTable;
extern TextTable lbl_80245188;
extern char lbl_8064B5D0[7];
extern char lbl_8064B5D8[8];
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern const int lbl_8064EBC8;
extern const int lbl_8064EBCC;
extern const float lbl_8064EBD0;
extern const float lbl_8064EBD4;
extern const float lbl_8064EBD8;
extern const float lbl_8064EBDC;
extern const float lbl_8064EBE0;
extern const float lbl_8064EBE4;
extern const float lbl_8064EBE8;
extern const float lbl_8064EBEC;
extern const float lbl_8064EBF0;
extern const float lbl_8064EBF4;
extern const int lbl_806519C0;

int fn_8008B08C(void* object, int state, void* event, int* resultOut)
{
    Vec3 position;
    Vec3 destination;
    Vec3 targetPosition;
    Vec3 savedPosition;
    Vec3 destinationCopy;
    Vec3 positionScratch;
    u8 color[4];
    int candidateCount;
    int searchRadius;
    int searchLimit;
    int colorA, colorB, colorC;
    ActorState* actor;
    void* tracking;
    void* resource;
    int objectId;
    ActionState* action;
    s8 mask;
    const TextTable* strings;
    ObjectInfo* info;
    int flags;
    int eventType;
    int randomDelay;
    int stateCode = state;

    strings = &lbl_80245188;
    eventType = fn_80200C10(event);
    resource = fn_80201BC8(object);
    info = fn_80201B8C(object);
    action = info->action;
    actor = info->actor;
    tracking = fn_80201B94(object);
    objectId = fn_80201B54(object);
    fn_8011F114(&position, resource);
    flags = lbl_8064D5A8 + info->flagOffset;
    mask = (s8) info->actor->mask;
    if (eventType == 3) {
        int countdown;

        fn_800CC4DC(object);
        countdown = actor->cooldown;
        if (countdown >= 1) {
            countdown -= 1;
        }
        actor->cooldown = countdown;
        countdown = actor->delay;
        if (countdown >= 1) {
            countdown -= 1;
        }
        actor->delay = countdown;
        fn_8008CC20(action);
        if (((u8) action->status == 0) && ((u8)fn_8008C93C(object, resource) != 0)) {
            void* player;
            int playerId;

            player = fn_80201B3C();
            playerId = fn_80201B54(player);
            fn_8011FA8C(resource, 0x40000000, 0);
            fn_8008CBE8(object, playerId);
            if ((fn_8008ABD4(object, player, (int)event, 0) != 0) && (fn_800462C8(1) != 0x17)) {
                fn_8020104C(8, objectId, objectId, 0, lbl_8064EBD0);
            }
        }
    }
    if (stateCode == 0x0) {
        if (eventType == 0x1) {
            fn_8008CBB8(action);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            action->searchTimer = 0;
            fn_80201E60(tracking, fn_80201CD4(tracking) | 4);
            fn_8011F778(resource, lbl_8064EBD4);
            return 1;
        } else if (eventType == 0x39) {
            fn_800EA3A0(object, actor);
            fn_8012B324(resource);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, (u32)object);
            fn_800CA2C8(object);
            fn_80204FDC(object);
            return 1;
        } else if (eventType == 0xEA) {
            fn_800674E4((int)object, (int)event);
            return 1;
        } else if (eventType == 0xEB) {
            fn_80067650(object, event);
            return 1;
        } else if (eventType == 0xC9) {
            if (fn_8011FF38() != 0) {
                fn_8011FA8C(resource, 0, 0x20000000);
                fn_801AAE68(0x1F1, 0x64, 0, lbl_8064EBD8, &position, 2, 2, 0, (u16) lbl_8064D18C, 0);
            }
            return 1;
        } else if (eventType == 0x4E) {
            if (resultOut != NULL) {
                *resultOut = 1;
            }
            return 1;
        } else if (eventType == 0x3E) {
            u32 objectFlags;

            objectFlags = (u32)fn_80036D5C(object);
            if (objectFlags & 0x08000000) {
                fn_80036DA4(object, (void*)(objectFlags & 0xF7FFFFFF));
                fn_801261F4(resource);
                colorC = lbl_8064EBCC;
                colorB = lbl_806519C0;
                colorA = lbl_8064EBC8;
                fn_8012C62C(resource, 0xF, &colorA, &colorB, &colorC, 4);
                fn_8011FA8C(resource, 0, 0x100);
            }
            fn_800BD194(object, actor);
            fn_800C9E50(object);
            fn_801D14CC(objectId);
            return 1;
        } else if (eventType == 0x3D) {
            fn_800EA3A0(object, actor);
            fn_800BD2DC(object, actor);
            return 1;
        } else if (eventType == 0x69) {
            fn_8005FF94(object, event, resultOut);
            return 1;
        } else if (eventType == 0x8) {
            fn_8008A6F8(object, event);
            return 1;
        } else if (eventType == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (eventType == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (eventType == 0xB) {
            int result;

            fn_801A7588(fn_80200C38(event), 0x8000);
            result = fn_800654F8((int)fn_80200C38(event));
            if (resultOut != NULL) {
                *resultOut = result;
            }
            return 1;
        } else if (eventType == 0x27) {
            fn_80064B38((int)object, event, resultOut);
            return 1;
        } else if (eventType == 0x3B) {
            int result;
            int colorEnabled;
            int eventFlags;

            result = 0;
            eventFlags = (int)fn_80200C38(event);
            fn_8012DBE8(resource, 0xF, color);
            colorEnabled = color[3] != 0;
            if (eventFlags & 5) {
                result = 1;
            } else {
                int playerHandle;
                int sourceId;

                playerHandle = fn_80201B44();
                sourceId = fn_80200C20(event);
                if (sourceId == playerHandle) {
                    void* player;
                    void* other;
                    int selected;

                    player = fn_80201B3C();
                    selected = fn_80049220(player, 1);
                    other = (void*)fn_80049304(player, selected);
                    if (other != NULL) {
                        ObjectInfo* otherInfo;

                        if (other != NULL) {
                            otherInfo = fn_80201B8C(other);
                        } else {
                            otherInfo = NULL;
                        }
                        if ((otherInfo != NULL) && ((u8) otherInfo->type != 0x13)) {
                            result = 1;
                        }
                    }
                } else {
                    void* other;

                    other = fn_80201814(sourceId);
                    if ((other != 0) && ((fn_80201B5C(other) == 0x19) || (fn_8003BF5C(other) != 0))) {
                        result = 1;
                    }
                }
            }
            if (!colorEnabled) {
                result = 0;
            }
            if (resultOut != NULL) {
                *resultOut = result;
            }
            return 1;
        } else if (eventType == 0xEF) {
            if (resultOut != NULL) {
                *resultOut = 1;
            }
            return 1;
        } else if (eventType == 0xF3) {
            void* eventData;

            eventData = fn_80200C38(event);
            fn_800EA0FC(object, actor, (int)eventData, event, resultOut);
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x5C) {
        if (eventType == 0x1) {
            fn_801294DC(resource, 0x30, 0x21, 1);
            fn_8008CAD4((int)action, resource, info->kind, 1);
            fn_8008CA84(&position);
            return 1;
        } else if (eventType == 0x3) {
            if (actor->flags & 0x400000) {
                fn_8008CA70(action);
                fn_8008CAD4((int)action, resource, info->kind, 0);
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (fn_8008C9AC(action) != 0) {
                fn_8008CA70(action);
                fn_8008CAD4((int)action, resource, info->kind, 0);
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (eventType == 0x5A) {
            int ownerId;
            void* eventData;

            ownerId = fn_80200C20(event);
            eventData = fn_80200C38(event);
            if (fn_8008C7F8(action, object, &actor->position, ownerId, eventData) != 0) {
                fn_8008CC50(fn_80200C38(event));
                fn_80201D2C(object, 0x5D);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x5D) {
        if (eventType == 0x1) {
            fn_801294DC(resource, 0x31, 0x21, 1);
            fn_8008CAD4((int)action, resource, info->kind, 2);
            fn_8008CA84(&position);
            return 1;
        } else if (eventType == 0x3) {
            if (actor->flags & 0x400000) {
                fn_8008CA70(action);
                fn_8008CAD4((int)action, resource, info->kind, 0);
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (fn_8008C9AC(action) != 0) {
                fn_8008CA70(action);
                fn_80201D2C(object, 0x5C);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (eventType == 0x5A) {
            int ownerId;
            void* eventData;

            ownerId = fn_80200C20(event);
            eventData = fn_80200C38(event);
            if (fn_8008C7F8(action, object, &actor->position, ownerId, eventData) != 0) {
                fn_8008CC50(fn_80200C38(event));
                fn_80201D2C(object, 0x5E);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x5E) {
        if (eventType == 0x1) {
            fn_801294DC(resource, 0x32, 0x21, 1);
            fn_8008CAD4((int)action, resource, info->kind, 3);
            fn_8008CA84(&position);
            return 1;
        } else if (eventType == 0x3) {
            if (actor->flags & 0x400000) {
                fn_8008CA70(action);
                fn_8008CAD4((int)action, resource, info->kind, 0);
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else if (fn_8008C9AC(action) != 0) {
                fn_8008CA70(action);
                fn_80201D2C(object, 0x5D);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (eventType == 0x5A) {
            int ownerId;
            void* eventData;

            ownerId = fn_80200C20(event);
            eventData = fn_80200C38(event);
            if (fn_8008C7F8(action, object, &actor->position, ownerId, eventData) != 0) {
                fn_8008CC50(fn_80200C38(event));
                if (fn_8008ABD4(object, fn_80201814(action->owner), (int)event, 0) != 0) {
                    action->cancelled = 0U;
                    if (fn_800462C8(1) != 0x17) {
                        fn_8020104C(8, objectId, objectId, 0, lbl_8064EBD0);
                    }
                } else {
                    fn_8008CBD4(action);
                }
            }
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x1) {
        if (eventType == 0x1) {
            fn_8011F778(resource, lbl_8064EBD4);
            return 1;
        } else if (eventType == 0x5A) {
            int ownerId;
            void* eventData;

            ownerId = fn_80200C20(event);
            eventData = fn_80200C38(event);
            if (fn_8008C7F8(action, object, &actor->position, ownerId, eventData) != 0) {
                fn_80201D2C(object, 0x15);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (eventType == 0x3) {
            fn_8008A914(object, flags, resource);
            if ((fn_8008AF24(object, resource, event, flags, mask) == 0) && !(info->actor->flags & 0x800000)) {
                int countdown;

                countdown = action->searchTimer;
                action->searchTimer = countdown < 1 ? 0 : countdown - 1;
                if (action->searchTimer == 0) {
                    const short** candidate;

                    searchRadius = 0x1F4;
                    searchLimit = 0x7FFE;
                    candidate = fn_800BC100(0, &position, &candidateCount, 8, &searchRadius, &searchLimit, 0);
                    if (candidate != NULL) {
                        fn_800BCCC4(*candidate, &destination);
                        fn_80201DD8(tracking, (void*)-1);
                        destinationCopy = destination;
                        fn_80201F44(object, &destinationCopy);
                        fn_800BDEE4(object, info->actor);
                        fn_80201D2C(object, 0x3E);
                        fn_80201D14(object, 1);
                    }
                }
            }
            return 1;
        } else if (eventType == 0x2) {
            randomDelay = fn_800FBFB0() & 0x3C;
            randomDelay += fn_800FBFB0() & 0x3C;
            action->searchTimer = randomDelay + 0xB4;
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x3E) {
        if (eventType == 0x1) {
            action->blockedCount = 0;
            return 1;
        } else if (eventType == 0x3D) {
            fn_800EA3A0(object, actor);
            fn_800BD2DC(object, actor);
            fn_8012B344(resource);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (eventType == 0x5A) {
            int ownerId;
            void* eventData;

            ownerId = fn_80200C20(event);
            eventData = fn_80200C38(event);
            if (fn_8008C7F8(action, object, &actor->position, ownerId, eventData) != 0) {
                fn_80201D2C(object, 0x15);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (eventType == 0x3) {
            fn_800BE010(object, actor);
            if ((int)fn_80201C48(tracking) != 0) {
                fn_800BDEE4(object, actor);
            }
            if (fn_8009A2B8(object, resource, (void*)objectId, actor, event, (void*)2, 0x50, 0, lbl_8064EBDC) != 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            } else {
                u32 objectFlags;
                u16 actionFlags;

                actionFlags = fn_8011FAF4(resource);
                objectFlags = fn_8011FAEC(resource);
                if (actionFlags & 2) {
                    fn_8011FABC(resource, 2, 0);
                    if (++action->blockedCount > 0x1E) {
                        fn_8012B344(resource);
                        fn_80201D2C(object, 1);
                        fn_80201D14(object, 1);
                    }
                } else if (objectFlags & 0x10) {
                    ActorState* runtime;

                    runtime = info->actor;
                    if (++runtime->attempts > 0xFU) {
                        runtime = info->actor;
                        runtime->attempts = 0U;
                        fn_8012B344(resource);
                        fn_80201D2C(object, 1);
                        fn_80201D14(object, 1);
                    }
                }
            }
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x15) {
        if (eventType == 0x1) {
            fn_8012B344(resource);
            return 1;
        } else if (eventType == 0x3) {
            if ((fn_8008AF24(object, resource, event, flags, mask) == 0) && (fn_800BE86C(resource, &actor->position, 2, 0, lbl_8064EBE0) == 0)) {
                if (fn_8008C9BC(action, info) != 0) {
                    fn_8008CBA4(action);
                    fn_80201D2C(object, 0x5C);
                    fn_80201D14(object, 1);
                } else {
                    fn_8012B344(resource);
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            }
            return 1;
        } else if (eventType == 0x5A) {
            return 1;
        } else if (eventType == 0x2) {
            int movementType;
            u16 movementFlags;

            movementType = fn_80128EAC(resource);
            movementFlags = fn_801290D0(resource);
            if ((movementFlags & 4) && ((movementType == 3) || (movementType == 2))) {
                fn_80128F74(resource, movementFlags & 0xFFFFFFFB);
            }
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x3) {
        if (eventType == 3) {
            struct { void* handle; } target;
            void* targetObject;

            if (!(flags & mask)) {
                fn_800359A0(object, 0);
            }
            target.handle = fn_80201C48(tracking);
            if ((target.handle != 0) && ((targetObject = fn_80201814((int)target.handle)) != 0)) {
                int distance;

                fn_802045AC(object, &targetPosition);
                distance = fn_80179064((s32) position.x, (s32) position.y, (s32) targetPosition.x, (s32) targetPosition.y);
                if ((distance < (s32) fn_800CB444(object, targetObject)) && (fn_80204578(object, &targetPosition) != 0)) {
                    if (fn_8008A96C(object, resource, event) == 0) {
                        fn_80201D2C(object, 1);
                        fn_80201D14(object, 1);
                    }
                } else {
                    fn_800CCC78(object, 0x1F4);
                    if (fn_8008ABCC(object, fn_80201814((int)target.handle), event) == 0) {
                        if (fn_8012AFC4(resource) != 0) {
                            fn_80129928(resource, &targetPosition);
                        } else {
                            fn_8012976C(resource, 2, 0x21, &targetPosition, lbl_8064EBE4);
                        }
                    }
                }
            } else {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (eventType == 0x66) {
            fn_8012B344(resource);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x6) {
        if (eventType == 0xC) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (eventType == 0x7) {
            if (fn_80035FB8(object, strings->name, lbl_8064B5D0, strings->interrupted, lbl_8064B5D8, strings->idleMessage) == 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        } else if (eventType == 0xD) {
            if ((u8) action->cancelled != 0) {
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
                fn_8012B344(resource);
            }
            return 1;
        } else if (eventType == 0x4E) {
            if (resultOut != NULL) {
                *resultOut = 0;
            }
            return 1;
        } else if (eventType == 0xEA) {
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x1F) {
        if (eventType == 0x1) {
            fn_800CC860(object, 2, 3);
            fn_800BE8D4(objectId);
            fn_800CA2C8(object);
            fn_80204FDC(object);
            return 1;
        } else if (eventType == 0x30) {
            int result;

            result = fn_800654F8((int)fn_80200C38(event));
            if (resultOut != NULL) {
                *resultOut = result;
            }
            return 1;
        } else if (eventType == 0x3D) {
            fn_800EA3A0(object, actor);
            fn_800BD2DC(object, actor);
            fn_8020123C(0x39, objectId, objectId, 0);
            return 1;
        } else if (eventType == 0x11) {
            fn_800EA3A0(object, actor);
            fn_800CF598(object);
            fn_80120AD0(resource, 0, 0, 0x101, lbl_8064EBE8, lbl_8064EBEC);
            fn_80201D34(object, 0x15);
            fn_80201D1C(object, 1);
            fn_801294DC(resource, 0x28, 1, 0xA);
            return 1;
        } else if (eventType == 0x31) {
            fn_8003C114(object, resource, objectId);
            return 1;
        } else if (eventType == 0x7) {
            const char* text;

            text = strings->assertion;
            fn_80035FB8(object, strings->name, strings->finishingResponse, strings->interrupted, text, text);
            return 1;
        } else if (eventType == 0x4E) {
            if (resultOut != NULL) {
                *resultOut = 0;
            }
            return 1;
        } else if (eventType == 0x3B) {
            return 1;
        } else if (eventType == 0x35) {
            return 1;
        } else if (eventType == 0x32) {
            return 1;
        } else if (eventType == 0x8) {
            return 1;
        } else if (eventType == 0xB) {
            return 1;
        } else if (eventType == 0x27) {
            return 1;
        } else if (eventType == 0xEA) {
            return 1;
        }
        goto unhandled;
    } else if (stateCode == 0x8) {
        if (eventType == 0x1) {
            fn_8011FA8C(resource, 0xC0, 0);
            fn_8008CAD4((int)action, resource, info->kind, 0);
            fn_800CC860(object, 1, 0);
            fn_800BE8D4(objectId);
            fn_800CA2C8(object);
            fn_80204FDC(object);
            return 1;
        } else if (eventType == 0xC2) {
            fn_800CA1BC(object, resource, event, resultOut);
            return 1;
        } else if (eventType == 0x3D) {
            fn_800EA3A0(object, actor);
            fn_800BD2DC(object, actor);
            fn_8020123C(0x39, objectId, objectId, 0);
            return 1;
        } else if (eventType == 0x33) {
            fn_8020123C(0x39, objectId, objectId, 0);
            return 1;
        } else if (eventType == 0x11) {
            if (fn_8003C04C(object) != 0) {
                if ((int)fn_8011FB4C(resource) == 0xBE) {
                    fn_8011F114(&positionScratch, resource);
                    savedPosition = positionScratch;
                    fn_8011F104(resource, lbl_8064EBEC, lbl_8064EBEC, lbl_8064EBF0);
                    fn_8013B83C(resource);
                    fn_8011F0E8(resource, &savedPosition);
                    fn_8011FABC(resource, 0, 0x8000);
                }
                fn_800EA3A0(object, actor);
                fn_800CF598(object);
                fn_80120AD0(resource, 0, 0, 0x101, lbl_8064EBE8, lbl_8064EBEC);
                fn_801294DC(resource, 0x28, 0x21, 0xA);
                fn_80201D34(object, 0x15);
                fn_80201D1C(object, 1);
            }
            return 1;
        } else if (eventType == 0xB) {
            void* eventData;

            eventData = fn_80200C38(event);
            if (fn_801A74C0(eventData) & 0x20) {
                int result;

                result = fn_800654F8((int)eventData);
                fn_8020123C(0x2F, objectId, objectId, 0);
                fn_8020104C(0x31, objectId, objectId, 0, lbl_8064EBF4);
                if (resultOut != NULL) {
                    *resultOut = result;
                }
            }
            return 1;
        } else if (eventType == 0x4E) {
            if (resultOut != NULL) {
                *resultOut = 0;
            }
            return 1;
        } else if (eventType == 0x2) {
            fn_802006D4(objectId, objectId, 8, 0x11, 0);
            return 1;
        } else if (eventType == 0x3B) {
            return 1;
        } else if (eventType == 0x35) {
            return 1;
        } else if (eventType == 0x32) {
            return 1;
        } else if (eventType == 0x8) {
            return 1;
        } else if (eventType == 0x27) {
            return 1;
        } else if (eventType == 0xEA) {
            return 1;
        }
        goto unhandled;
    } else {
        return 0;
    }
unhandled:
    return 0;
}
