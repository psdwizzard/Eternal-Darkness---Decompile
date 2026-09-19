typedef unsigned short u16;
typedef unsigned char u8;

typedef struct ActorState {
    char pad_000[0x64];
    void *resource;
    char pad_068[0x1FC];
    void *effect;
} ActorState;

extern int fn_80200C10(void *);
extern void* fn_80201B3C();
extern int fn_80201B54();
extern int fn_80200C20(void *);
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void fn_8011F114();
extern int fn_80201B44();
extern void fn_80201DD8(int, int);
extern void fn_800359A0(void *, int);
extern void fn_800A3104(ActorState *, int);
extern void fn_800A3AC4(ActorState *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_800CC4DC(void *);
extern int fn_800A3588(ActorState *, void *, void *, void *, int);
extern int fn_800D39D0(ActorState *, void *, void *, int);
extern void fn_801AC9F4(u16, int, float *, int);
extern int fn_8013017C(void *);
extern int fn_801305D4(void *);
extern void fn_801301B0(void *, int, int);
extern void fn_80201E78(void *, void *);
extern void fn_800A3894(ActorState *, float *, void *);
extern void fn_800A2598(ActorState *);
extern void fn_800A3274(ActorState *, void *, int);
extern void fn_8020123C(int, int, int, int);
extern void fn_800A2D1C(ActorState *);
extern void fn_801557C4(void *, int);
extern void fn_800CD094(void *, void *, int);
extern int lbl_8064D5A8;

/*
 * Honest-C work in progress for the 9,520-byte actor event dispatcher.  The
 * common setup and the complete early event-3, event-1, and event-8 paths are
 * recovered here; the many later event branches remain to be expressed before
 * this can be considered for a matching build.
 */
int fn_800D0B74(void *object, int alternate, void *event, int value)
{
    int kind = fn_80200C10(event);
    void *source = fn_80201B3C();
    int source_id = source != 0 ? fn_80201B54(source) : -1;
    int event_value = fn_80200C20(event);
    void *resource = fn_80201BC8(object);
    void *actor = fn_80201B8C(object);
    ActorState *state = *(ActorState **)((u8 *)actor + 0x64);
    void *actor_8c = *(void **)((u8 *)actor + 0x8C);
    int mode = (int)fn_80201B94(object);
    int object_id = fn_80201B54(object);
    float position[3];
    int active = fn_80201B44();

    fn_8011F114(position, resource);
    fn_80201DD8(mode, active);

    if (kind == 3) {
        u16 actor_kind = *(u16 *)((u8 *)state + 0x86);
        int special = actor_kind != 2;
        int handled;
        float source_position[3];

        fn_800CC4DC(object);
        handled = fn_800A3588(state, object, (u8 *)state + 0x88, source,
                              special);
        handled |= fn_800D39D0(state, object, source, 1);
        if (handled != 0) {
            fn_801AC9F4(**(u16 **)((u8 *)state + 0x264), 0x64, position, 2);
        }
        ((void (**)(void *, void *))*(void **)state)[4](object, state);
        if ((fn_8013017C(resource) & 0x40) != 0 &&
            fn_801305D4(resource) == 0) {
            fn_801301B0(resource, 0x40, 0);
        }
        if ((lbl_8064D5A8 & 0xF) == 0) {
            fn_80201E78(source_position, source);
            fn_800A3894(state, position, source_position);
        }
    }

    if (alternate == 0 && kind == 1) {
        void (**callbacks)(ActorState *, void *);
        fn_800359A0(object, 0);
        fn_80201DD8(mode, 0);
        fn_800A3104(state, 0);
        fn_800A3AC4(state);
        callbacks = *(void (***)(ActorState *, void *))state;
        callbacks[0](state, object);
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
        return 1;
    }

    if (alternate == 0 && kind == 8) {
        fn_800A2598(state);
        fn_800A3274(state, object, 3);
        ((void (**)(ActorState *, void *, void *))*(void **)state)[8](
            state, object, event);
        fn_8020123C(0xFC, object_id, source_id, 0);
        fn_800A2D1C(state);
        fn_801557C4(*(void **)((u8 *)state + 0xC4), 1);
        fn_801557C4(*(void **)((u8 *)state + 0xC8), 1);
        *(void **)((u8 *)state + 0xC4) = 0;
        *(void **)((u8 *)state + 0xC8) = 0;
        fn_800CD094(object, event, 0xB4);
        return 1;
    }

    (void)source_id;
    (void)event_value;
    (void)object_id;
    (void)actor_8c;
    (void)value;
    return 0;
}
