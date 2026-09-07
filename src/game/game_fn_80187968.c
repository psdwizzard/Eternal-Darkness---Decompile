typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const float lbl_80650A50;
extern u8 lbl_802FC5BC[];

typedef struct EffectConfig {
    u8 pad00;
    u8 field_01;
    u8 field_02;
    s8 field_03;
    u16 field_04;
    u8 pad06[0xE];
    u32 field_14;
    u32 field_18;
    u32 field_1C;
    u32 field_20;
    u8 field_24;
    u8 field_25;
    u8 field_26;
    u8 field_27;
    u8 pad28[2];
    u16 field_2A;
    float field_2C;
    u32 field_30;
    u32 field_34;
} EffectConfig;

void fn_80187968(void* value)
{
    EffectConfig* config = value;

    config->field_01 = 0x20;
    config->field_04 = 6;
    config->field_02 = 0xFC;
    config->field_03 = -4;
    config->field_14 = 0;
    config->field_18 = 0;
    config->field_1C = 0;
    config->field_24 = 5;
    config->field_25 = 0xFF;
    config->field_20 = 0;
    config->field_30 = *(u32*)(lbl_802FC5BC + 0xC);
    config->field_34 = *(u32*)(lbl_802FC5BC + 0xC);
    config->field_2A = 0x258;
    config->field_26 = 0x94;
    config->field_2C = lbl_80650A50;
    config->field_27 = 0xF0;
}
