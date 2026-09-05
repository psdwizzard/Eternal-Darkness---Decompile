typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct Descriptor {
    u32 word;
    u16 half;
} Descriptor;

typedef struct EffectParams {
    u8 pad00[4];
    u16 value04;
    u16 value06;
    u8 pad08[8];
    void* object10;
    f32 angle14;
    u8 value18;
    u8 pad19[3];
    u32 flag1C;
    u32 value20;
    u8 pad24[0x6C];
} EffectParams;

extern u32 lbl_80651EA0;
extern u16 lbl_80651EA4;
extern const f32 lbl_80651038;
extern const f32 lbl_8065103C;
extern const f32 lbl_80651040;
extern void fn_801CECB4(u32, s16*);
extern void fn_801905CC(EffectParams*);
extern u32 fn_801D38E8(u32);
extern s16 fn_801CEB2C(u32);
extern f32 fn_80048C2C(f32);
extern f32 fn_80048C50(f32);
extern void* fn_801D3988(s16, u32);
extern void* fn_80148008(Vec3f*, Descriptor*, EffectParams*, void (*)(void));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern void fn_8017FE0C(void*, u32);
extern void fn_8019045C(void);

void fn_801CE744(u32 type, u32 value, const Vec3f* position, u16 index,
                 u32 value20, u8 value18, void** objects, f32 base_angle,
                 f32 radius)
{
    Descriptor descriptor;
    Vec3f position_copy;
    Vec3f submit_position;
    s16 indices[10];
    EffectParams params;
    u32 object_type;
    s16 count;
    int i;

    fn_801CECB4(type, indices);
    fn_801905CC(&params);
    params.value20 = value20;
    params.value18 = value18;
    if (index == 0) {
        params.flag1C = 1;
    } else {
        params.value06 = index;
    }

    object_type = fn_801D38E8(type);
    count = fn_801CEB2C(type);
    for (i = 0; i < count; i++) {
        f32 angle = base_angle + lbl_80651038 * i / count;
        void* object = 0;
        void* effect;
        descriptor.word = lbl_80651EA0;
        descriptor.half = lbl_80651EA4;
        position_copy.x = position->x + radius * (lbl_8065103C * fn_80048C2C(angle));
        position_copy.y = position->y + radius * (lbl_8065103C * fn_80048C50(angle));
        position_copy.z = lbl_80651040 + position->z;
        params.value04 = indices[i];
        params.object10 = fn_801D3988(indices[i], object_type);
        submit_position = position_copy;
        effect = fn_80148008(&submit_position, &descriptor, &params, fn_8019045C);
        if (effect != 0) {
            object = fn_80156938(effect);
            if (object != 0) {
                fn_8017FF1C(object, 4);
                fn_8017FE0C(object, value);
            }
        }
        if (objects != 0) {
            objects[i] = object;
        }
    }
}
