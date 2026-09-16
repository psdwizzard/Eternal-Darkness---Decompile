typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Owner8009F700 {
    u8 pad00[0x20];
    u32 flags;
} Owner8009F700;

typedef struct State8009F700 {
    u8 pad00[0x38];
    void* field_38;
    u8 pad3C[0x2C];
    u8 field_68;
    u8 pad69[0x5B];
    Owner8009F700* owner;
} State8009F700;

typedef struct Context8009F700 {
    u32 kind;
    u8 pad04[4];
    s16 counter;
} Context8009F700;

typedef struct RuntimeInner8009F700 {
    u8 pad00[0x44];
    void* field_44;
} RuntimeInner8009F700;

typedef struct Runtime8009F700 {
    u8 pad00[0x8C];
    RuntimeInner8009F700* field_8C;
} Runtime8009F700;

extern Context8009F700* fn_8006ED98(State8009F700*);
extern void fn_8006DEF8(State8009F700*, int, void*, void*, int);
extern void fn_80201814(void*);
extern Runtime8009F700* fn_80201B8C(void);
extern void fn_8020123C(int, int, void*, int);

int fn_8009F700(register State8009F700* state)
{
    Context8009F700* context;
    Owner8009F700* owner;
    int result = 0;
    Runtime8009F700* runtime;

    context = fn_8006ED98(state);
    owner = state->owner;
    if (owner->flags & 0x2000) {
        context->counter++;
        owner->flags &= ~0x2000u;
    }
    if (context->counter >= 3) {
        for (result = 0; result < 4; result++) {
            state->field_68 = result;
            fn_8006DEF8(state, context->kind, 0, 0, 0);
        }
        fn_80201814(state->field_38);
        runtime = fn_80201B8C();
        fn_8020123C(81, 0, runtime->field_8C->field_44, 0);
        result = 1;
    }
    return result;
}
