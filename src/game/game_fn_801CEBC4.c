typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Descriptor {
    u32 word;
    u16 half;
} Descriptor;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Effect {
    u8 pad00;
    u8 value01;
    u8 pad02;
    s8 value03;
    u16 value04;
    u16 value06;
    u16 value08;
    u8 pad0A[0xA];
    u8 value14;
    u8 pad15[3];
    u8 value18;
    u8 value19;
    u8 pad1A[2];
    u16 value1C;
    u8 pad1E[0x32];
    float value50;
    u8 pad54[0x24];
    u32 value78;
    u8 pad7C[0x14];
    void (*callback90)(void);
    void* object94;
    Vec3f position98;
    u8 descriptorA4[6];
    u8 valueAA;
} Effect;

extern u32 lbl_80651EB0;
extern u16 lbl_80651EB4;
extern const float lbl_8065105C;
extern void fn_801858E0(Effect*);
extern void fn_80185AE8(void);
extern void* memcpy(void*, const void*, u32);
extern void fn_801E8328(int, Effect*);

void fn_801CEBC4(Effect* effect, const Vec3f* position, u8 value14,
                 u16 value08, u16 value04, const u32* value78)
{
    Descriptor descriptor;

    descriptor.word = lbl_80651EB0;
    descriptor.half = lbl_80651EB4;
    fn_801858E0(effect);
    effect->value04 = value04;
    effect->value01 = 0x30;
    effect->value08 = value08;
    effect->value06 = value08 + 8;
    effect->value03 = -30;
    effect->value14 = value14;
    effect->value1C = effect->value01;
    effect->value18 |= 2;
    effect->value19 = 5;
    effect->value50 = lbl_8065105C;
    effect->value78 = *value78;
    effect->callback90 = fn_80185AE8;
    effect->position98 = *position;
    memcpy(effect->descriptorA4, &descriptor, 6);
    effect->object94 = 0;
    effect->valueAA = 4;
    fn_801E8328(0x10, effect);
}
