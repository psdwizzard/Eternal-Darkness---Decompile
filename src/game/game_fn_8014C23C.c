typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Effect {
    u8 fields[0x90];
    void* (*callback)(void*, void*, void*);
    void* runtime;
    Vec3 position;
    u8 direction[6];
    u8 type;
    u8 tail[4];
} Effect;
typedef struct Setup {
    u32 first;
    u32 second;
    u32 direction_word;
    u16 direction_tail;
    u16 pad;
    Vec3 position;
} Setup;

extern u32 lbl_806504C4;
extern u32 lbl_806504C8;
extern u32 lbl_80651BE8;
extern u16 lbl_80651BEC;
extern const float lbl_806504CC;
extern const float lbl_806504D0;
extern const float lbl_806504D4;

extern void fn_8018F76C(Effect*);
extern void fn_8018F808(Effect*, Vec3*, void*);
extern void* fn_8018F864(void*, void*, void*);
extern void* memcpy(void*, const void*, unsigned int);
extern void* fn_80147EC4(Effect*);
extern void fn_801568B8(void*, int);
extern void fn_80180AC8(void*, int);
extern int fn_801A98F4(int, int);

#pragma opt_common_subs off
void fn_8014C23C(u16 kind, u8 variant, s8 strength)
{
    Setup setup;
    Effect effect;
    void* object;

    setup.second = lbl_806504C4;
    setup.first = lbl_806504C8;
    setup.direction_word = lbl_80651BE8;
    setup.direction_tail = lbl_80651BEC;
    setup.position.x = lbl_806504CC;
    setup.position.y = lbl_806504D0;
    setup.position.z = lbl_806504D4;
    fn_8018F76C(&effect);
    if (kind != 0) {
        *(u16*)((u8*)&effect + 6) = kind + 255;
        *(u16*)((u8*)&effect + 8) = kind;
    }
    if (variant != 0)
        ((u8*)&setup)[3] = variant;
    if (strength != 0)
        ((u8*)&effect)[3] = strength;
    ((u8*)&effect)[0x28] = 0;
    fn_8018F808(&effect, (Vec3*)&setup.second, &setup.first);
    effect.callback = fn_8018F864;
    effect.position = setup.position;
    memcpy(effect.direction, &setup.direction_word, 6);
    effect.runtime = 0;
    effect.type = 1;
    object = fn_80147EC4(&effect);
    if (object != 0) {
        fn_801568B8(object, 0);
        if (effect.runtime != 0) {
            fn_80180AC8(effect.runtime, 1);
            fn_801A98F4(536, 100);
        }
    }
}

#pragma opt_common_subs reset
