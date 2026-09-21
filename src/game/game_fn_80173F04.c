typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3s { short x, y, z; } Vec3s;
typedef struct Vec3f { float x, y, z; } Vec3f;
/* Four-byte aggregate copied through a local before entering EffectParams. */
typedef struct Value32 { u32 word; } Value32;
typedef struct Descriptor { u32 word; u16 half; } Descriptor;
typedef struct EffectParams {
    u8 pad0[2]; u8 value2; signed char value3; u8 pad4[2]; u16 value6;
    u8 pad8[0xC];
    u8 value14, value15, value16, value17, value18, value19, value1A, pad1B;
    Value32 value1C;
    u8 pad20[0x70];
} EffectParams;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_8018358C(EffectParams*);
extern u8* fn_80183454(void*, void*, void*);
extern void* fn_80148008(Vec3f*, Descriptor*, EffectParams*, u8* (*)(void*, void*, void*));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern const u32 lbl_80651CA8;
extern const u16 lbl_80651CAC;
extern const Value32 lbl_806506FC;
extern const char lbl_8024FF00[];

int fn_80173F04(void* arg)
{
    void* state = arg;
    int resource;
    int kind;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;
    Vec3s* source;
    Descriptor descriptor;
    Value32 value;
    Vec3f position;
    Vec3f submit_position;
    EffectParams params;

    descriptor.word = lbl_80651CA8;
    descriptor.half = lbl_80651CAC;
    value = lbl_806506FC;

    if (fn_8016A598(state) != 11) {
        fn_80163BB4(state, lbl_8024FF00, 11, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    kind = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    arg4 = fn_8016A694(state, 4);
    arg5 = fn_8016A694(state, 5);
    arg6 = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);
    arg8 = fn_8016A694(state, 8);
    arg9 = fn_8016A694(state, 9);
    arg10 = fn_8016A694(state, 10);
    arg11 = fn_8016A694(state, 11);

    source = fn_80158ABC(fn_8015C4A4(resource, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;

    fn_8018358C(&params);
    params.value2 = arg10;
    params.value3 = arg11;
    params.value6 = arg9;
    params.value17 = arg3;
    params.value18 = arg4;
    params.value16 = arg5;
    params.value14 = arg6;
    params.value15 = arg7;
    params.value19 = arg8;
    params.value1C = value;
    if (kind == 1) params.value1A = 2;

    submit_position = position;
    {
        void* effect = fn_80148008(&submit_position, &descriptor, &params, fn_80183454);
        if (effect != 0) fn_8017FF1C(fn_80156938(effect), 4);
    }
    return 0;
}
