typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct Work {
    u8 pad00[0x3C];
    int handle0;
    int handle1;
    int handle2;
    u8 pad48[0x2C];
    Vec3 position;
    float value;
    u8 pad84[0x24];
    u32 saved_flags;
} Work;

typedef struct State {
    u8 pad00[0x38];
    void* object_id;
    u8 pad3C[0x88];
    Work* work;
} State;

typedef struct Actor {
    u8 pad00[0x44];
    void* child_id;
    u8 pad48[0x70];
    u32 flags;
} Actor;

extern void *fn_80201814();
extern void *fn_80201BC8();
extern Actor* fn_80036D38(void*);
extern void* fn_80158598(void*, int);
extern int fn_80157FE0(void*, int, int);
extern float fn_8012B750(void*);
extern void fn_8011F114();
extern void fn_801E79A0(void*, int);
extern void fn_80067180(void*);
extern void* lbl_8064C4E0;

int fn_800A0CC0(State* arg)
{
    register volatile State* state = arg;
    register Work* work;
    register void* object;
    register void* indexed;
    register void* context;
    register Actor* actor;
    Vec3 position;

    object = fn_80201814(state->object_id);
    context = fn_80201BC8(object);
    fn_80201814(fn_80036D38(object)->child_id);
    work = state->work;
    indexed = fn_80158598(state->object_id, 0);
    work->handle0 = fn_80157FE0(indexed, 1, 0);
    work->handle1 = fn_80157FE0(indexed, 2, 0);
    work->handle2 = fn_80157FE0(indexed, 4, 0);
    work->value = fn_8012B750(context);
    fn_8011F114(&position, context);
    work->position = position;
    actor = fn_80036D38(object);
    fn_801E79A0(lbl_8064C4E0, 0x3AA);
    if (actor != 0) {
        work->saved_flags = actor->flags;
        actor->flags |= 0xF;
    }
    fn_80067180(object);
    return 1;
}
