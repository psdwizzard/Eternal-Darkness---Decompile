typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Particle {
    u8 pad_0[0xA];
    s16 x;
    s16 y;
    s16 z;
    s16 dx;
    s16 dy;
    s16 dz;
    u8 pad_16[0xB];
    u8 alpha;
    u8 pad_22[6];
    u32 colour0;
    u32 colour1;
    u32 colour2;
    u32 colour3;
} Particle;

typedef struct EffectState {
    u16 phase;
    u16 field_2;
    float field_4;
    float age;
    float step;
    u8 values[32];
    u8 field_30;
} EffectState;

extern float lbl_80650D10;
extern u32 lbl_80607440[];
extern int lbl_8064D18C;
extern void fn_801EF384(void*);
extern int rand(void);
extern void fn_801A29E0(void*);

int fn_801A1F8C(u8* object)
{
    EffectState* state;
    Particle* particle;
    float scale;
    float limit;
    int count;
    int i;
    int spawned;

    fn_801EF384(object);
    state = (EffectState*)(object + 0x8C);
    particle = *(Particle* volatile*)((u8*)state - 0x40);
    scale = *(volatile float*)(object + 0x90);
    limit = *(volatile float*)(object + 0x94);
    count = *(volatile u8*)(object + 1);

    if (limit < scale) {
        scale = limit;
        state->age = limit + state->step;
    }

    for (i = 0; i < count; i++, particle++) {
        int value;
        int clamped;
        if ((state->phase ^ 1) != 0) {
            float t = scale;
            if (scale >= lbl_80650D10) {
                particle->x = particle->x + particle->dx * t;
                particle->y = particle->y + particle->dy * t;
                particle->z = particle->z + particle->dz * t;
            } else {
                t = state->phase * scale;
                if (t >= lbl_80650D10) {
                    particle->x = particle->x + particle->dx * t;
                    particle->y = particle->y + particle->dy * t;
                    particle->z = particle->z + particle->dz * t;
                }
            }
        }

        value = state->values[i] + (rand() % 3);
        value++;
        clamped = value > 255 ? 255 : value;
        state->values[i] = clamped;
        particle->colour0 = lbl_80607440[state->values[i]];
        particle->colour1 = lbl_80607440[state->values[i]];
        particle->colour2 = lbl_80607440[state->values[i]];
        particle->colour3 = lbl_80607440[state->values[i]];
        {
            float alpha = 40.0f * (0.5f + (255.0f - state->values[i]) / 255.0f);
            particle->alpha = (u8)(alpha * scale);
        }
    }

    particle = *(Particle**)(object + 0x4C);
    state->phase++;
    if (state->phase >= 4) {
        float spawn_alpha;
        state->phase = 0;
        spawn_alpha = 60.0f * scale;
        spawned = 0;
        for (i = 0; i < count; particle++, i++) {
            int index = i;
            if (state->values[index] == 255) {
                int random;
                random = rand();
                particle->x = *(s16*)(object + 0x10) + scale * (10 - random % 20);
                random = rand();
                particle->y = *(s16*)(object + 0x12) + scale * (10 - random % 20);
                particle->z = *(s16*)(object + 0x14);
                state->values[index] = 0;
                particle->dx = 1 - (rand() & 1);
                particle->dy = 1 - (rand() & 1);
                particle->dz = (rand() & 1) + 1;
                spawned++;
                particle->colour0 = lbl_80607440[state->values[index]];
                particle->colour1 = lbl_80607440[state->values[index]];
                particle->colour2 = lbl_80607440[state->values[index]];
                particle->colour3 = lbl_80607440[state->values[index]];
                particle->alpha = (u8)spawn_alpha;
                if (spawned == 1) {
                    break;
                }
            }
        }
    }

    (*(u16*)(object + 0xA))++;
    if (*(u16*)(object + 0xA) >= *(u16*)(object + 0xC)) {
        if (*(u16*)(object + 0xC) != 0) {
            fn_801A29E0(object);
        }
    }
    if (state->field_30 != 0 && lbl_8064D18C != *(int*)(object + 0x38)) {
        *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
