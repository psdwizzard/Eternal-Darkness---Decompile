typedef unsigned char u8;

typedef struct Runtime80095894 {
    u8 pad00[0x68];
    void* target;
} Runtime80095894;

typedef struct State80095894 {
    u8 pad00[0xD8];
    int timer;
} State80095894;

extern void *fn_80201B8C();
extern int fn_800931D0(void*, void*, void*);
extern int fn_80092C30(void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

int fn_80095894(register void* object, void* unused,
                register void* state, register State80095894* context)
{
    register Runtime80095894* runtime;
    register int timer;

    runtime = ((Runtime80095894*)fn_80201B8C(object));
    timer = context->timer;
    context->timer = timer > 0 ? timer - 1 : 0;
    if (fn_800931D0(object, state, context) ||
        fn_80092C30(object, runtime->target) || context->timer == 0) {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    }
    return 0;
}
