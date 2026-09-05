typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Work {
    u8 pad00[0x3C];
    int handle0, handle1, handle2;
    u8 pad48[0x18];
    s16 value0, value1, value2, value3;
    u8 pad68[0x0C];
    Vec3 position;
    float scale;
    u8 pad84[0x24];
    u32 saved_flags;
} Work;
typedef struct Context {
    u8 pad00[0x38];
    void* object_id;
    u8 pad3C[0x88];
    Work* work;
} Context;
typedef struct Actor { u8 pad00[0xB8]; u32 flags; } Actor;
typedef struct LinkedInfo { void* value; } LinkedInfo;
typedef struct LinkedValue { u8 pad00[0x18]; int value; } LinkedValue;

#pragma use_lmw_stmw on

extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern Context* fn_8006D444(void);
extern void fn_801A5C30(int);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8014C23C(int, int, int);
extern void fn_8012C478(void*, int, int);
extern int fn_80201B54();
extern void* fn_80158598(void*, int);
extern void* fn_80201C24();
#define fn_80201C24(a) ((LinkedInfo*)fn_80201C24(a))
extern void fn_80157E34(void*, int, int, int, int);
extern void* fn_8004918C(void);
extern void fn_8004948C(void*, void*, int);
extern int fn_800389E0(void*, int, s16, int);
extern void fn_8011F104(void*, float, float, float);
extern void fn_8012B7A0(void*, float);
extern void fn_801D13D8(void*, int);
extern Actor* fn_80036D38(void*);
extern void fn_801E79A0(void*, int);
extern void fn_800A18AC(int);
extern void* lbl_8064C4E0;
extern int lbl_8064D18C;

#pragma opt_lifetimes off
int fn_800A0DE4(void* state)
{
    Context* context;
    Work* work;
    void* object;
    void* transform;
    void* linked;
    void* indexed;
    Actor* actor;

    fn_80204844(fn_80201B9C(state), 0x20);
    context = fn_8006D444();
    fn_801A5C30(0);
    object = fn_80201814(context->object_id);
    transform = fn_80201BC8(object);
    work = context->work;
    fn_8014C23C(0, 0, 0);
    fn_8012C478(transform, 0, 1);
    fn_8012C478(transform, 1, 1);
    fn_8012C478(transform, 2, 1);
    fn_8012C478(transform, 3, 1);

    if (work->handle1 != -1) {
        linked = fn_80201814((void*)work->handle1);
        if (linked != 0) {
            indexed = fn_80158598(((void*)fn_80201B54(object)), 0);
            fn_80157E34(indexed, work->handle1, 2,
                        ((LinkedValue*)fn_80201C24(linked)->value)->value, 0);
            fn_8004948C(object, fn_8004918C(), 0);
        }
        work->handle1 = -1;
    }
    if (work->handle0 != -1) {
        linked = fn_80201814((void*)work->handle0);
        if (linked != 0) {
            indexed = fn_80158598(((void*)fn_80201B54(object)), 0);
            fn_80157E34(indexed, work->handle0, 1,
                        ((LinkedValue*)fn_80201C24(linked)->value)->value, 0);
        }
        work->handle0 = -1;
    }
    if (work->handle2 != -1) {
        linked = fn_80201814((void*)work->handle2);
        if (linked != 0) {
            indexed = fn_80158598(((void*)fn_80201B54(object)), 0);
            fn_80157E34(indexed, work->handle2, 4,
                        ((LinkedValue*)fn_80201C24(linked)->value)->value, 0);
        }
        work->handle2 = -1;
    }
    fn_800389E0(object, 0, work->value0, 0);
    fn_800389E0(object, 2, work->value1, 0);
    fn_800389E0(object, 3, work->value2, 0);
    fn_800389E0(object, 1, work->value3, 0);
    fn_8011F104(transform, work->position.x, work->position.y, work->position.z);
    fn_8012B7A0(transform, work->scale);
    fn_801D13D8(context->object_id, 0);
    actor = fn_80036D38(object);
    if (actor != 0) actor->flags = work->saved_flags;
    fn_801E79A0(lbl_8064C4E0, 0x3AA);
    fn_800A18AC(lbl_8064D18C);
    return 0;
}
#pragma opt_lifetimes reset
