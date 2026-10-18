typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectDescriptor {
    u8 variant;
    u8 mode;
    u8 pad02[2];
    u16 type;
    u8 pad06[0x12];
    u32 value18;
    u8 pad1C[0x74];
    void (*callback)(void);
    u8 pad94[4];
    Vec3 position;
    u16 valueA4;
    u16 valueA6;
    u16 lifetime;
    u8 size;
} EffectDescriptor;

extern void fn_80181F5C(EffectDescriptor*);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern s32 fn_801D3A24(s32, s32);
extern void fn_80182014(void);
extern void fn_80147EC4(EffectDescriptor*);

void fn_80031948(Vec3* position, s32 object_id)
{
    EffectDescriptor effect;

    fn_80181F5C(&effect);
    effect.mode = 4;
    effect.variant = (rand() & 0xF) + 0x11;
    effect.type = fn_801D3A24(object_id, 0x42);
    effect.value18 = 0;
    effect.callback = fn_80182014;
    effect.position = *position;
    effect.valueA4 = 0;
    effect.valueA6 = 0;
    effect.lifetime = (rand() & 7) + 7;
    effect.size = 4;
    fn_80147EC4(&effect);
}
