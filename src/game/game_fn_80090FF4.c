typedef struct ActorState {
    unsigned char pad[0x167];
    unsigned char counter;
} ActorState;

typedef struct Timers {
    unsigned char pad[0x1C];
    short first;
    short second;
} Timers;
typedef struct Object Object;
typedef struct Actor Actor;
typedef struct Context Context;

extern int fn_80201B54();
extern int fn_8011FAEC(void*);
extern void fn_800BE010(void*, void*);
extern int fn_80201C48(void*);
extern void fn_800BDEE4(void*, void*);
extern unsigned short fn_8012DBE8(void*, int, void*);
extern void fn_800BE8D4(void*);
extern unsigned int fn_8011FA8C(void*, int, int);
extern int fn_8013017C(void*);
extern int fn_801305D4(void*);
extern void fn_801301B0(void*, int, int);

void fn_80090FF4(Object* object, Actor* actor, ActorState* state,
                 Context* arg4, Timers* timers)
{
    unsigned char value[4];
    int flags;
    void* owner;

    owner = ((void*)fn_80201B54(object));
    flags = fn_8011FAEC(actor);

    timers->first = 1 >= timers->first ? 0 : timers->first - 1;
    timers->second = 1 >= timers->second ? 0 : timers->second - 1;
    fn_800BE010(object, state);
    if (fn_80201C48(arg4) != 0) {
        fn_800BDEE4(object, state);
    }
    fn_8012DBE8(actor, 15, value);
    if (value[3] < 20) {
        fn_800BE8D4(owner);
    }
    if (flags & 0x10) {
        fn_8011FA8C(actor, 16, 0);
        state->counter++;
    }
    if ((fn_8013017C(actor) & 0x40) && fn_801305D4(actor) == 0) {
        fn_801301B0(actor, 0x40, 0);
    }
}
