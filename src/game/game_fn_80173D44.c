typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3s { short x, y, z; } Vec3s;
typedef struct Vec3f { float x, y, z; } Vec3f;
typedef struct Descriptor { u32 word; u16 half; } Descriptor;
typedef struct EffectParams {
    u8 pad0[2]; u8 value2; signed char value3; u8 pad4[2]; u16 value6;
    u8 pad8[0xC];
    u8 value14, value15, value16, value17, value18, value19, value1A, pad1B;
    u32 value1C;
    u8 pad20[0x70];
} EffectParams;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_8018358C(EffectParams*);
extern u8* fn_801834F0(void*, void*, void*);
extern void* fn_80148008(Vec3f*, Descriptor*, EffectParams*,
                         u8* (*)(void*, void*, void*));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern u32 lbl_80651CA0;
extern u16 lbl_80651CA4;
extern u32 lbl_806506F4;
extern const float lbl_806506F8;
extern const char lbl_8024FF00[];

int fn_80173D44(void* arg)
{
    void* state = arg;
    int resource;
    int kind;
    Vec3s* source;
    Descriptor descriptor;
    volatile u32 value;
    Vec3f position;
    Vec3f submit_position;
    EffectParams params;
    descriptor.word = lbl_80651CA0;
    descriptor.half = lbl_80651CA4;
    value = lbl_806506F4;
    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, lbl_8024FF00, 2, fn_8016A598(state));
        return 0;
    }
    resource = fn_800F5C54(fn_8016A694(state, 1));
    kind = fn_8016A694(state, 2);
    source = fn_80158ABC(fn_8015C4A4(resource, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z - lbl_806506F8;
    fn_8018358C(&params);
    params.value2 = 250;
    params.value3 = -5;
    params.value6 = 20;
    params.value17 = 10;
    params.value18 = 1;
    params.value14 = 10;
    params.value15 = 250;
    params.value19 = 2;
    params.value1C = value;
    if (kind == 1) params.value1A = 2;
    submit_position = position;
    {
        void* effect = fn_80148008(&submit_position, &descriptor, &params, fn_801834F0);
        if (effect != 0) fn_8017FF1C(fn_80156938(effect), 4);
    }
    return 0;
}
