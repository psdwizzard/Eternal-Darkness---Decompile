typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ReactionState {
    u8 padding[0x150];
    short timer;
} ReactionState;

typedef struct ActorData {
    u8 padding[0x8C];
    ReactionState *state;
} ActorData;

extern u32 fn_801A7498(void *effect);
extern u32 fn_801A7490(void *effect);
extern void *fn_80201814(int id);
extern void *fn_80201B8C(u8 *object);
extern int fn_8003BD48(void *object, void *effect);
extern u8 fn_80128EE4(void *object);
extern void *fn_801A717C(void);
extern void fn_8012B344(void *object);
extern void fn_801A7470(void *effect, u32 kind);
extern void fn_801A74A0(void *effect, u32 id);
extern void fn_801A74A8(void *effect, u32 id);
extern unsigned long long fn_8020123C(int kind, int source, int target, int effect);
extern void fn_801A7228(void *effect);

int fn_8009376C(void *object, register void *effect)
{
    register void *resolved;
    register void *saved_object;
    register u32 source;
    register u32 target;
    register int result;
    register ActorData *data;

    /* ASM: mr, mr, li preserve the working-pointer copy and initialization
     * order. MWCC coalesces the copy and assigns the owner register first in C. */
    asm {
        mr resolved, effect
        mr saved_object, r3
        li result, 0
    }
    source = fn_801A7498(resolved);
    target = fn_801A7490(resolved);
    resolved = fn_80201814(source);
    fn_80201814(target);
    if (resolved != 0 && saved_object != 0) {
        data = fn_80201B8C(resolved);
        result = fn_8003BD48(saved_object, effect);
        if (fn_80128EE4(saved_object) & 0x20) {
            if (result & 3) {
                void *owner = saved_object;
                saved_object = fn_801A717C();
                data->state->timer = 120;
                fn_8012B344(owner);
                fn_801A7470(saved_object, 0x30);
                fn_801A74A0(saved_object, source);
                fn_801A74A8(saved_object, source);
                fn_8020123C(0x35, source, source, (int)saved_object);
                fn_801A7228(saved_object);
            } else if (result & 0x40) {
                void *owner = saved_object;
                saved_object = fn_801A717C();
                fn_8012B344(owner);
                fn_801A7470(saved_object, 0xB);
                fn_801A74A0(saved_object, source);
                fn_801A74A8(saved_object, source);
                fn_8020123C(0x35, source, source, (int)saved_object);
                fn_801A7228(saved_object);
            }
        }
    }
    return result;
}
