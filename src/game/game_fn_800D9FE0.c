typedef unsigned char u8;
typedef signed short s16;

typedef struct Actor {
    u8 pad0[0x284];
    s16 timer;
} Actor;

extern void *fn_801A7498(void *);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern int fn_8003BD48(void *, void *);

#pragma opt_propagation off
int fn_800D9FE0(void *context, void *object)
{
    void *saved_context = context;
    Actor *actor;
    void *saved_object = object;

    actor = *(Actor **)((u8 *)fn_80201B8C(fn_80201814(fn_801A7498(saved_object))) +
                        0x64);
    if (actor->timer == 0 &&
        (fn_8003BD48(saved_context, saved_object) & 3) != 0) {
        actor->timer = 0xD2;
    }
    return 1;
}
#pragma opt_propagation reset
