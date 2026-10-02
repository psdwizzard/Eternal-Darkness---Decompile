typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct EffectState {
    u16 field_0;
    u16 field_2;
    float field_4;
    float field_8;
    float field_C;
    u8 values[32];
} EffectState;

typedef struct Entry {
    u8 pad_0[0x28];
    u32 colors[4];
} Entry;

typedef struct EffectObject {
    u8 pad_0[0x4C];
    Entry* entry;
    u8 pad_50[0x3C];
    EffectState state;
    u8 field_BC;
    u8 field_BD;
} EffectObject;

typedef struct EffectConfig {
    u8 count;
    u8 pad_1[0x13];
    float value;
    u8 field_18;
    u8 divisor;
} EffectConfig;

extern const float lbl_80650D1C;
extern u32 lbl_80607440[];
extern void fn_801A1F8C(void*);

void fn_801A1E14(EffectObject* object, EffectConfig* config)
{
    EffectState* state;
    Entry* entry;
    float initial;
    int count;
    int i;

    initial = lbl_80650D1C;
    state = &object->state;
    state->field_0 = 0;
    state->field_2 = 0;
    object->field_BD = 0;
    state->field_8 = initial;
    state->field_4 = config->value;
    object->field_BC = config->field_18;

    if (config->divisor != 0) {
        state->field_8 = initial;
        state->field_C = state->field_4 / config->divisor;
    } else {
        state->field_8 = state->field_4;
    }

    count = config->count;
    entry = object->entry;
    for (i = 0; i < count; i++) {
        state->values[i] = 0xFF;
        entry->colors[0] = lbl_80607440[state->values[i]];
        entry->colors[1] = lbl_80607440[state->values[i]];
        entry->colors[2] = lbl_80607440[state->values[i]];
        entry->colors[3] = lbl_80607440[state->values[i]];
    }

    fn_801A1F8C(object);
}
