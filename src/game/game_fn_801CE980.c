typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
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

typedef struct EffectParams {
    u8 pad00[4];
    u16 value04;
    u16 value06;
    u8 pad08[8];
    void* object10;
    u8 value14;
    u8 value15;
    u8 pad16[6];
    u8 payload1C[0x18];
    u8 pad34[0x5C];
} EffectParams;

extern u32 lbl_80651EA8;
extern u16 lbl_80651EAC;
extern Vec3f lbl_8023B558;
extern void* lbl_806333A0[];
extern void fn_80190638(EffectParams*);
extern void* memcpy(void*, const void*, u32);
extern void* fn_801D3988(s16, u32);
extern void* fn_80148008(Vec3f*, Descriptor*, EffectParams*, void (*)(void));
extern void fn_801903C4(void);
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);

void fn_801CE980(int slot, u16 value04, u8 value14, u8 value15,
                 const void* payload, u16 value06, u32 object_type)
{
    Descriptor descriptor;
    Vec3f initial_position = lbl_8023B558;
    Vec3f position;
    EffectParams params;
    void* effect;
    void* object;

    descriptor.word = lbl_80651EA8;
    descriptor.half = lbl_80651EAC;
    fn_80190638(&params);
    params.value04 = value04;
    params.value06 = value06;
    params.value14 = value14;
    params.value15 = value15;
    memcpy(params.payload1C, payload, 0x18);
    params.object10 = fn_801D3988((s16)value04, object_type);
    position = initial_position;
    effect = fn_80148008(&position, &descriptor, &params, fn_801903C4);
    if (effect != 0) {
        object = fn_80156938(effect);
        if (object != 0) {
            fn_8017FF1C(object, 4);
        }
        if (slot >= 0) {
            lbl_806333A0[slot] = object;
        }
    }
}
