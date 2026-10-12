typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct State800A3AF8 {
    u8 pad000[0x86];
    u16 state;
    u8 transform[0xD8];
    void* resource;
    u8 pad164[0x34];
    int slot;
} State800A3AF8;

typedef struct Context800A3AF8 {
    u8 pad000[0x64];
    State800A3AF8* state;
} Context800A3AF8;

extern void* fn_80201B8C(void*);
extern int fn_800A2130(void*);
extern void* fn_80201BC8(void*);
extern void fn_800A49FC(void*, int*, void*);
extern void fn_800A3274(State800A3AF8*, u32, u32);
extern void fn_800A3AC4(State800A3AF8*);
extern int fn_80201B54(void*);
extern int fn_800A2018(State800A3AF8*, u16);
extern int fn_800A2E64();
extern int fn_800A2FCC();
extern void* fn_80201B3C(void);
extern int fn_800A36F4(State800A3AF8*, void*, void*);
extern void fn_800A2E00(State800A3AF8*, void*, void*);
extern void fn_80201D2C(void*, int);
extern void fn_80201D14(void*, u8);

/* The body matches retail. With this unit's existing compiler settings,
 * register saves use _savegpr_26/_restgpr_26 instead of stmw/lmw.
 */
int fn_800A3AF8(void* object)
{
    void* current;
    int next;
    int animation;
    Context800A3AF8* context;
    State800A3AF8* state;
    int changed;

    animation = -1;
    changed = 0;
    context = fn_80201B8C(object);
    state = context->state;
    next = fn_800A2130(object);

    if (state->state != next) {
        void* target = fn_80201BC8(object);
        changed = 1;
        fn_800A49FC(target, &state->slot, context);
        fn_800A3274(state, (u32)object, next);
        fn_800A3AC4(state);
        switch (next) {
        case 0:
        case 1:
        case 2:
            animation = 0x49;
            break;
        case 3:
            break;
        }
        if (animation != -1) {
            void* owner = (void*)fn_80201B54(object);
            int resource_id = fn_800A2018(state, state->state);
            fn_800A2E64(state, resource_id);
            fn_800A2FCC(state->transform, state->resource, resource_id, owner, 0);
            current = fn_80201B3C();
            fn_800A36F4(state, state->transform, current);
            fn_800A2E00(state, owner, (void*)0x319);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
        }
    }
    return changed;
}
