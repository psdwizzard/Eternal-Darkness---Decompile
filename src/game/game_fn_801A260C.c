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

int fn_801A260C(u8* object)
{
    EffectState* state;
    Particle* particle;
    float scale;
    int count;
    int i;

    fn_801EF384(object);
    state = (EffectState*)(object + 0x8C);
    particle = *(Particle**)(object + 0x4C);
    scale = state->field_4;
    count = object[1];

    if (state->age < scale) {
        scale = state->age;
        state->age = state->age + state->step;
    }

    for (i = 0; i < count; i++, particle++) {
        int clamped;
        int value;
        float alpha;
        if ((state->phase ^ 1) != 0) {
            float t = scale;
            if (scale >= lbl_80650D10) {
                particle->x = (s16)(particle->x + particle->dx * t);
                particle->y = (s16)(particle->y + particle->dy * t);
                particle->z = (s16)(particle->z + particle->dz * t);
            } else {
                t = state->phase * scale;
                if (t >= lbl_80650D10) {
                    particle->x = (s16)(particle->x + particle->dx * t);
                    particle->y = (s16)(particle->y + particle->dy * t);
                    particle->z = (s16)(particle->z + particle->dz * t);
                }
            }
        }

        value = state->values[i] + (rand() % 3);
        value += 1;
        clamped = value <= 255 ? value : 255;
        state->values[i] = clamped;
        particle->colour0 = lbl_80607440[state->values[i]];
        particle->colour1 = lbl_80607440[state->values[i]];
        particle->colour2 = lbl_80607440[state->values[i]];
        particle->colour3 = lbl_80607440[state->values[i]];
        alpha = 40.0f * (0.5f + (255.0f - state->values[i]) / 255.0f);
        particle->alpha = (u8)(alpha * scale);
    }

    (*(u16*)(object + 0xA))++;
    if (*(u16*)(object + 0xA) >= *(u16*)(object + 0xC)) {
        *(u16*)(object + 0x22) = 8;
    }
    if (state->field_30 != 0 && lbl_8064D18C != *(int*)(object + 0x38)) {
        *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
