typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Particle {
    u8 pad00[0xA];
    s16 position[3];
    s16 velocity[3];
    u8 pad16[6];
    s16 value1C;
    u8 pad1E[0xD];
    u8 alpha;
    u8 pad2C[0xC];
} Particle;

typedef struct ChainState {
    int owner;
    int target;
    int source;
    u8 flags;
    u8 pad0D;
    u8 update_a;
    u8 update_b;
    u8 update_c;
    u8 interval;
    u8 next_start;
    u8 started;
    u8 done_mask;
    u8 value15;
    u8 value16;
    u8 values[7];
    u8 sound;
    u8 triggered;
    u8 finished;
    u8 pad21;
    s16 value22;
    float value24;
    float value28;
    u8 data2C[0x10];
} ChainState;

typedef struct EffectObject {
    u8 pad00;
    u8 count;
    u8 alpha;
    u8 pad03;
    u8 value04;
    u8 pad05[5];
    u16 timer;
    u8 pad0C[4];
    u8 data10[0x12];
    u16 value22;
    u8 data24[0x28];
    Particle* particles;
    u8 pad50[0xF];
    u8 value5F;
    u8 data60[0x2C];
    ChainState state;
} EffectObject;

extern void fn_801991E0(void*, void*, int);
extern int fn_80180430(void*, u8);
extern void fn_80180518(void*, int, int);
extern void fn_8017E850(void*, void*, short, float, void*);
extern void fn_8017E958(void*, void*, short, float);
extern void fn_8017D700(void*, void*, short, void*, int, u8, u8, u8);
extern int fn_8017D1E0(void*, void*, u16, u16, u16, s16*);
extern u8 fn_8018E26C(u8*, u8*);
extern void fn_8018E230(u8*, u8*, int, int, int, u8);
extern int fn_800AD2B4(void);
extern int fn_800AD538(void);
extern int fn_800AD4E8(void);
extern void fn_8020123C(int, int, int, int);
extern void fn_8020104C(int, int, int, int, float);
extern void* fn_80201814(int);
extern void* fn_80201BC8(void*);
extern u16 fn_8006749C(int);
extern void fn_80120AD0(void*, int, int, u16, float, float);

extern int lbl_8064D18C;
extern const float lbl_80650D50;
extern const float lbl_80650D54;
extern const float lbl_80650D68;
extern const float lbl_80650D6C;

int fn_801A3DF8(EffectObject* object)
{
    int mask;
    ChainState* state = &object->state;
    Particle* channel;
    unsigned int count;
    u8 update_a;
    u8 update_b;
    u8 update_c;
    int i;
    u8 any_active;
    float step;

    if (state->flags & 4) {
        fn_801991E0(object, state->data2C, 0x10);
        goto finish;
    }

    count = object->count;
    any_active = 0;
    step = lbl_80650D50 / (float)count;
    channel = object->particles;
    update_a = state->update_a;
    update_b = state->update_b;
    update_c = state->update_c;
    if (state->started < count && object->timer >= state->next_start) {
        channel[state->started].alpha = object->alpha;
        fn_80180518(object->data24, state->started, 1);
        state->started++;
        state->next_start += state->interval;
    }

    for (i = 0; i < (int)count; channel++, i++) {
        if (!fn_80180430(object->data24, i))
            continue;
        if (state->done_mask & (mask = 1 << i)) {
            if (i == 0)
                fn_8017E850(channel->position, object->data10,
                            state->value22, state->value28,
                            &state->value24);
            else
                fn_8017E958(channel->position, object->data10,
                            state->value22,
                            state->value24 + (float)i * step);
            continue;
        }
        any_active = 1;
        {
            s16 value = state->values[i];

            fn_8017D700(channel->position, object->data10,
                        channel->value1C, channel->velocity,
                        value, update_b, update_a, update_c);
            if (fn_8017D1E0(channel->position, object->data10,
                            state->value15, (u16)state->value22, state->value16,
                            &value)) {
                if (state->triggered == 0) {
                    void* owner = fn_80201814(state->target);
                    if (owner != 0) {
                        void* resolved = fn_80201BC8(owner);
                        if (resolved != 0) {
                            u16 base_flags = fn_8006749C(state->sound);
                            u16 flags = base_flags | 2;
                            fn_80120AD0(resolved, 0, 100, flags,
                                        lbl_80650D54, lbl_80650D68);
                        }
                    }
                    state->triggered = 1;
                    if (state->flags & 0x80)
                        fn_8020123C(0xEA, state->source,
                                    state->target, 0);
                }
                state->done_mask |= mask;
            } else {
                state->values[i] = (u8)value;
            }
        }
    }

    if (!(state->flags & 0x80) && !state->finished && !any_active) {
        if (lbl_8064D18C == 0x29)
            fn_8020123C(0xEA, state->source, state->target, -1);
        if (fn_800AD2B4()) {
            if (state->target == fn_800AD538()) {
                if (!fn_800AD4E8())
                    fn_8020123C(0x39, state->owner, state->owner, 0);
                else
                    fn_8020104C(0x39, state->owner, state->owner, 0,
                                lbl_80650D6C);
            } else {
                fn_8020104C(0xC4, state->owner, state->owner, 0,
                            lbl_80650D6C);
            }
        } else {
            fn_8020104C(0xC4, state->owner, state->owner, 0,
                        lbl_80650D6C);
        }
        state->finished = 1;
    }

    if (object->data60[0]) {
        if (!fn_8018E26C(object->data60, &object->value5F) && !(state->flags & 1))
            object->value22 = 8;
    } else if (!(state->flags & 1)) {
        if (object->value5F &&
            (!fn_800AD2B4() || state->target != fn_800AD538()))
            fn_8018E230(object->data60, &object->value5F, 1, object->value5F, object->value04, 0);
        else
            object->value22 = 8;
    } else if (state->flags & 0x20) {
        state->flags &= ~0x20;
        if (object->value5F)
            fn_8018E230(object->data60, &object->value5F, 1, object->value5F, object->value04, 0);
    } else if (state->flags & 0x40) {
        state->flags &= ~0x40;
        if (object->value5F != object->alpha)
            fn_8018E230(object->data60, &object->value5F, 1, 0,
                        (s8)-object->value04, object->alpha);
    } else if (fn_800AD2B4() && state->target == fn_800AD538() &&
               !fn_800AD4E8()) {
        fn_8020123C(0x39, state->owner, state->owner, 0);
    }

finish:
    object->timer++;
    return 1;
}
