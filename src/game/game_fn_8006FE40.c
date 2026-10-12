typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Actor Actor;
typedef struct Entry {
    void *object;
    u8 pad04[4];
    s16 count;
    u8 pad0A[0x16];
    void (*callback)(Actor *);
} Entry;
typedef struct Resource {
    u8 pad00[0x1780];
    int value;
} Resource;
typedef struct State {
    u8 pad00[0x20];
    u32 flags;
    u8 pad24[0x10];
    int status;
    u8 pad38[0x1e];
    u8 counter;
    u8 pad57[0x102];
    u8 active;
    u8 pad15A[2];
    Resource *resource;
} State;
struct Actor {
    void *base;
    Entry *entry;
    u8 pad08[8];
    void *item;
    u8 type;
    u8 enabled;
    u8 pending;
    u8 pad17[0x21];
    int handle;
    u8 pad3C[0x88];
    State *state;
};
typedef struct Context {
    u8 pad00[0x38];
    Actor *actor;
} Context;
typedef struct GlobalConfig {
    u8 pad00[0x10];
    u32 flags;
} GlobalConfig;
typedef struct GlobalState {
    u8 pad00[0x44];
    int current;
} GlobalState;

extern void fn_80008BD8(void *, int, int, int);
extern void fn_80008CA0(void);
extern GlobalState *fn_80036D38(void *);
extern int fn_8006BCE4(Actor *);
extern int fn_8006BD40(Actor *);
extern u8 fn_8006BFB4(void *, Actor *);
extern void fn_8006C89C(Actor *);
extern void fn_8006C92C(Actor *);
extern void fn_8006C9C0(void *);
extern void fn_8006C9D4(void *, unsigned short);
extern void fn_8006C9E4(void *, int);
extern void fn_8006C9F0(Actor *);
extern int fn_8006CACC(void *, int);
extern void fn_8006CB64(Actor *);
extern void fn_8006CEE4(void *);
extern int fn_8006CF74(Actor *);
extern int fn_8006D0A8(Actor *, void *);
extern void fn_8006D254(Actor *);
extern int fn_8006D344(Actor *, int, int);
extern void fn_8006E6EC(Actor *);
extern void *fn_8006EC74(Entry *);
extern void fn_8006F7E8(Actor *, int);
extern int fn_80070884(Actor *, void *);
extern int fn_80070CD8(void);
extern int fn_80070F74(Actor *);
extern void fn_80071550(int, int);
extern int fn_80071950(void *);
extern void fn_80071A58(void *);
extern void fn_800878F4(Actor *);
extern void fn_80088588(Actor *);
extern void fn_800A079C(Actor *);
extern void fn_800A1580(void *);
extern void fn_800AE954(void);
extern void fn_800AF11C(Actor *);
extern int fn_8011E84C(void);
extern int fn_8011E86C(void);
extern void *fn_80144710(int, int, int);
extern void fn_801ACD8C(void);
extern void fn_801AD404(int, int, int);
extern void fn_801AD490(void);
extern void fn_801AD4B4(int, int, int, int);
extern void fn_801AD528(int, int);
extern int fn_801AD5FC(int, int);
extern void fn_801E8328(int, void *);
extern void fn_801EFE84(int);
extern int fn_80200C10(void *);
extern void *fn_80200C38(void *);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8020123C(int, int, int, int);
extern void *fn_80201814(int);
extern int fn_80201B54(void *);
extern Context *fn_80201B8C(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_802020B4(void *, int);
extern int lbl_8064D18C;
extern int lbl_8064CBC0;
extern int lbl_8064D5A8;
extern float lbl_8064E7FC;
extern u8 lbl_80244024[];
extern GlobalConfig lbl_80332140;

int fn_8006FE40(void *object, int mode, void *event, int *handled)
{
    int code = fn_80200C10(event);
    Actor *actor = fn_80201B8C(object)->actor;
    int id = fn_80201B54(object);

    if (mode == 0) {
        if (code == 1) {
            fn_8006C92C(actor);
            fn_8006E6EC(actor);
            fn_800878F4(actor);
            fn_80088588(actor);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (code == 0x39) {
            void *target = fn_80201814(actor->handle);
            if (target != 0) {
                GlobalState *global = fn_80036D38(target);
                global->current = 0;
            }
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        }
        if (code == 0x3d) {
            fn_80071550(lbl_8064D18C, 0);
            if (fn_8006D344(actor, 0x62, 0)) {
                State *state = actor->state;
                state->resource->value = -1;
                state->active = 0;
            }
            return 1;
        }
        if (code == 0x3e) {
            fn_800A079C(actor);
            if (actor->enabled >= 1)
                fn_80071550(lbl_8064D18C, 1);
            fn_800AF11C(actor);
            if (fn_8006D344(actor, 0x800000, 0))
                actor->state->flags |= 0x8000U;
            return 1;
        }
        if (code == 0xde) {
            fn_80071A58((u8 *)actor->state + 5);
            actor->pending = 0;
            return 1;
        }
        if (code == 0xe9) {
            fn_801EFE84(0);
            return 1;
        }
        if (code == 0x5b) {
            int choice = (int)fn_80200C38(event);
            if (choice == 2 && fn_801AD5FC(1, 0)) {
                fn_801ACD8C();
                fn_801AD404(0, 0, 0x1e);
                fn_801AD490();
                fn_801AD404(0x64, 0x64, 1);
                fn_801AD4B4(choice, 0, 0, 0);
                fn_80008BD8(lbl_80244024, 3, 9, choice);
                actor->state->status = 0;
            }
            return 1;
        }
        if (code == 0x5c) {
            if ((int)fn_80200C38(event) == 2) {
                fn_80008CA0();
                fn_801ACD8C();
                fn_801AD404(0, 0, 0x64);
                fn_801AD490();
                fn_801AD528(1, 0x64);
            }
            return 1;
        }
        if (code == 0xbc) {
            actor->state->flags = __rlwinm(actor->state->flags, 0, 15, 13);
            return 1;
        }
    } else if (mode == 1) {
        if (code == 1)
            return 1;
        if (code == 0x53) {
            int result = 0;
            void **value = fn_80200C38(event);
            if (value != 0 && fn_8006D0A8(actor, *value)) {
                fn_80201D2C(object, 0x29);
                fn_80201D14(object, 1);
                result = 1;
            }
            fn_8006C9E4(actor->base, 0);
            if (handled != 0)
                *handled = result;
            return 1;
        }
        if (code == 0x50) {
            if (fn_8006CF74(actor)) {
                fn_80201D2C(object, 0x29);
                fn_80201D14(object, 1);
            } else {
                fn_8006C9E4(actor->base, 0xc1c);
            }
            fn_8006CEE4(actor->item);
            return 1;
        }
        if (code == 3) {
            void *target = fn_80201814(actor->handle);
            if (target != 0) {
                actor->type = fn_8006BFB4(target, actor);
                fn_8006C9C0(actor->base);
                fn_8006CB64(actor);
                if (lbl_8064CBC0 != 0) {
                    if ((u8)lbl_8064D5A8 == 0) {
                        if (actor->enabled != 0) {
                            fn_8006C89C(actor);
                            fn_8020123C(0x50, id, id, 0);
                        }
                        fn_8006C9E4(actor->base, 0);
                    }
                } else if (fn_8006CACC(actor->base, 0xe10)) {
                    if (actor->enabled != 0) {
                        fn_8006C89C(actor);
                        fn_8020123C(0x50, id, id, 0);
                        fn_8006C9E4(actor->base, 0);
                    } else {
                        fn_8006C9E4(actor->base, 0xc1c);
                    }
                }
                fn_8006D254(actor);
            }
            return 1;
        }
    } else if (mode == 0x29) {
        if (code == 1) {
            if (actor->entry->callback != 0)
                actor->entry->callback(actor);
            if (!((u32)fn_8006EC74(actor->entry) & 2)) {
                fn_800A1580(actor->entry->object);
                if (fn_80070CD8())
                    fn_8020104C(0x54, id, id, 0, lbl_8064E7FC);
                else
                    fn_8020123C(0x52, id, id, 0);
            }
            fn_8006C9E4(actor->base, 0);
            return 1;
        }
        if (code == 0x52) {
            fn_8006C9E4(actor->base, 0xc1c);
            fn_8006C9D4(actor->entry, 0);
            actor->entry = 0;
            lbl_80332140.flags = __rlwinm(lbl_80332140.flags, 0, 31, 29);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (code == 0x54) {
            int result = 0;
            fn_800A1580(actor->entry->object);
            if (fn_80070CD8()) {
                fn_80201D2C(object, 0x2a);
                fn_80201D14(object, 1);
                fn_8006C9E4(actor->base, 0);
                result = 1;
            } else {
                fn_8020123C(0x52, id, id, 0);
            }
            if (handled != 0)
                *handled = result;
            return 1;
        }
        if (code == 3) {
            void *target = fn_80201814(actor->handle);
            if (target != 0)
                actor->type = fn_8006BFB4(target, actor);
            fn_8006C9C0(actor->base);
            if (fn_8006CACC(actor->base, 0x1f40) || !fn_8006BD40(actor))
                fn_8020123C(0x52, id, id, 0);
            fn_8006D254(actor);
            return 1;
        }
    } else if (mode == 0x2a) {
        if (code == 1) {
            fn_8006C9F0(actor);
            return 1;
        }
        if (code == 0x52) {
            if (fn_80070F74(actor)) {
                fn_80070884(actor, object);
                fn_802020B4(object, 1);
            }
            return 1;
        }
        if (code == 0x56) {
            State *state = actor->state;
            u8 count = state->counter;
            state->counter = count + 1;
            fn_800AE954();
            return 1;
        }
        if (code == 0x51) {
            fn_8006F7E8(actor, 0);
            return 1;
        }
        if (code == 3) {
            void *target = fn_80201814(actor->handle);
            if (target != 0)
                actor->type = fn_8006BFB4(target, actor);
            fn_80070884(actor, object);
            switch (fn_8006BCE4(actor)) {
            case 0x16:
                if (actor->entry->count > 1 && fn_8011E84C() == 2 &&
                    (fn_8011E86C() == 1 || fn_8011E86C() == 3 ||
                     fn_8011E86C() == 4) && fn_80144710(0x200, 0, 0) != 0)
                    fn_8020123C(0x51, id, id, 0);
                break;
            case 0x22:
                if (!fn_80071950(target))
                    fn_8020123C(0x52, id, id, 0);
                break;
            }
            fn_8006D254(actor);
            return 1;
        }
        if (code == 2) {
            fn_802020B4(object, 1);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
