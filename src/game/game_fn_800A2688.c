typedef unsigned char u8;
typedef unsigned short u16;

typedef struct State800A2688 {
    u8 pad000[0x194];
    u16 current;
    u8 pad196[0xCA];
    u16 saved;
} State800A2688;

typedef struct Context800A2688 {
    u8 pad000[0x64];
    State800A2688* state;
} Context800A2688;

extern void *fn_80201B8C();
extern int fn_800A30C0(State800A2688*);
extern void fn_800A3C4C(void*, Context800A2688*, int, int);
extern void fn_800A3104(State800A2688*, int);

#pragma opt_propagation off
int fn_800A2688(void* object, void* source)
{
    void* current;
    Context800A2688* context;
    State800A2688* state;

    current = object;
    context = ((Context800A2688*)fn_80201B8C(source));
    state = context->state;

    if (!fn_800A30C0(state)) {
        fn_800A3C4C(current, context, 1, 1);
        fn_800A3104(state, 1);
        state->current = state->saved;
    }
    return 1;
}
#pragma opt_propagation reset
