typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;

#pragma use_lmw_stmw on

typedef struct EffectConfig {
    float reset_time;
    float duration;
    s32 count;
    s32 random_min;
    s32 random_max;
    float phase_step;
    u8 pad18[4];
    float cooldown_step;
    u8 pad20[4];
} EffectConfig;

typedef struct EffectState {
    u8 pad00[0x7C];
    float phase_time;
    float cooldown;
    u8 pad84[2];
    s16 timer;
    s8 kind;
} EffectState;

extern EffectConfig lbl_80243C30[];
extern const double lbl_8064E5C0;
extern const float lbl_8064E5DC;
extern const float lbl_8064E5E0;

extern unsigned int rand(void);
#define rand() ((int)rand())
extern s32 fn_8005EF94(void *, s32, s32 *, s32, s32);
extern void fn_8005F8D0(s32, void *, void *, void *, EffectState *, u8,
                       s32, s32, s32);
extern void fn_8005FCD4(s32, void *, void *, void *, EffectState *, u8);

void fn_8005FD84(s32 owner, void *entry, void *manager, void *source,
                 EffectState *state)
{
    s32 selected;

    if (state->timer != 0) {
        return;
    }

    selected = fn_8005EF94(entry, 0x1DB, 0, 0, 0);
    state->cooldown -= lbl_80243C30[state->kind].cooldown_step;

    if (state->cooldown <= lbl_8064E5DC) {
        s32 i;

        state->cooldown = lbl_80243C30[state->kind].reset_time;
        if (state->kind == 0) {
            state->cooldown += (rand() & 0x1F) +
                               (rand() & 0x1F) +
                               (rand() & 0x1F) +
                               (rand() & 0x3F);
        }

        for (i = 0; i < lbl_80243C30[state->kind].count; i++) {
            fn_8005F8D0(owner, entry, manager, source, state, state->kind,
                        0, 0, 1);
        }
    }

    if (selected != 0) {
        state->phase_time += lbl_80243C30[state->kind].phase_step;
        if (state->phase_time > lbl_80243C30[state->kind].duration) {
            state->cooldown = lbl_8064E5E0;
            state->phase_time = lbl_8064E5DC;
            if (++state->kind >= 5) {
                fn_8005FCD4(owner, entry, manager, source, state, state->kind);
                state->kind = 0;
            }
        }
    } else {
        state->kind = 0;
    }
}
