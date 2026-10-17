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

/* These views match the anonymous Data types in the accessor units. */
typedef struct { u8 pad[0x88]; u32 value; } EffectKindData;
typedef struct { u8 pad[0x98]; u32 value; } EffectTargetData;
typedef struct { u8 pad[0x9C]; u32 value; } EffectSourceData;

typedef struct Entry80201814 {
    struct Entry80201814 *prev;
    struct Entry80201814 *next;
    int unk8;
    int unkC;
    int id;
} Entry80201814;

extern u32 fn_801A7498(EffectSourceData *effect);
extern u32 fn_801A7490(EffectTargetData *effect);
extern Entry80201814 *fn_80201814(int id);
extern void *fn_80201B8C(u8 *object);
extern int fn_8003BD48(void *object, void *effect);
extern u8 fn_80128EE4(void *object);
extern void *fn_801A717C(void);
extern void fn_8012B344(void *object);
extern void fn_801A7470(EffectKindData *effect, u32 kind);
extern void fn_801A74A0(EffectSourceData *effect, u32 id);
extern void fn_801A74A8(EffectTargetData *effect, u32 id);
extern unsigned long long fn_8020123C(int kind, int source, int target, int effect);
extern void fn_801A7228(void *effect);

int fn_8009376C(void *object, register void *effect)
{
    register EffectSourceData *effect_view;
    register void *saved_object;
    register u32 source;
    register int result;
    register void *resolved;
    register u32 target;
    register ActorData *data;

    effect_view = (EffectSourceData *)effect;
    saved_object = (void *)object;
    result = 0;
    source = fn_801A7498(effect_view);
    target = fn_801A7490((EffectTargetData *)effect_view);
    resolved = fn_80201814(source);
    fn_80201814(target);
    if (resolved != 0 && saved_object != 0) {
        data = fn_80201B8C(resolved);
        result = fn_8003BD48(saved_object, effect);
        if (fn_80128EE4(saved_object) & 0x20) {
            if (result & 3) {
                void *reaction = fn_801A717C();
                data->state->timer = 120;
                fn_8012B344(saved_object);
                fn_801A7470(reaction, 0x30);
                fn_801A74A0(reaction, source);
                fn_801A74A8(reaction, source);
                fn_8020123C(0x35, source, source, (int)reaction);
                fn_801A7228(reaction);
            } else if (result & 0x40) {
                void *reaction = fn_801A717C();
                fn_8012B344(saved_object);
                fn_801A7470(reaction, 0xB);
                fn_801A74A0(reaction, source);
                fn_801A74A8(reaction, source);
                fn_8020123C(0x35, source, source, (int)reaction);
                fn_801A7228(reaction);
            }
        }
    }
    return result;
}
