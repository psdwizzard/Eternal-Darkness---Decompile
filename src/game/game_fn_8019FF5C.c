typedef signed char s8;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EffectParams {
    u8 type;
    u8 count;
    u8 field_02;
    s8 field_03;
    s16 field_04;
    u16 field_06;
    u16 field_08;
    u8 pad_0A[6];
    void* field_10;
    float field_14;
    float field_18;
    float field_1C;
    u8 field_20;
    u8 field_21;
    u8 pad_22[0x6E];
} EffectParams;

typedef struct GlobalData {
    u8 pad[12];
    void* field_0C;
} GlobalData;

extern void* memset(void* dst, int value, u32 size);
extern int rand(void);
extern GlobalData lbl_802FC5BC;
extern const float lbl_80650C98;
extern const float lbl_80650C9C;
extern float lbl_80650CA0;

void fn_8019FF5C(EffectParams* params)
{
    float value_18;
    float value_1C;
    float value_14;

    memset(params, 0, sizeof(EffectParams));
    params->type = 0x20;
    params->count = 4;
    params->field_02 = 0xFF;
    params->field_03 = -5;
    params->field_04 = 0x55;
    params->field_06 = (rand() & 3) + 2;
    value_14 = lbl_80650C98;
    value_1C = lbl_80650C9C;
    params->field_08 = params->field_06;
    value_18 = lbl_80650CA0;
    params->field_10 = lbl_802FC5BC.field_0C;
    params->field_20 = 2;
    params->field_21 = 0;
    params->field_14 = value_14;
    params->field_1C = value_1C;
    params->field_18 = value_18;
}
