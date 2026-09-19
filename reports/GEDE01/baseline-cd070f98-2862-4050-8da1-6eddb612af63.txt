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
    u8 pad18[4];
    u8 value1C;
    u8 pad1D[3];
    u32 flag20;
    u32 value24;
    u8 pad28[0x68];
} EffectParams;

extern u32 lbl_80651E98;
extern u16 lbl_80651E9C;
extern const f32 lbl_80651038;
extern const f32 lbl_8065103C;
extern const f32 lbl_80651040;
extern void fn_801CECB4(u32, s16*);
extern void fn_80190558(EffectParams*);
extern u32 fn_801D38E8(u32);
extern s16 fn_801CEB2C(u32);
extern f32 fn_80048C2C(f32);
extern f32 fn_80048C50(f32);
extern void* fn_801D3988(s16, u32);
extern void* fn_80148008(Vec3f*, Descriptor*, EffectParams*, void (*)(void));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern void fn_80190320(void);

void fn_801CE384(u32 type, const Vec3f* position, u16 value, u32 value24,
                 u8 value1C, void** objects)
{
    Descriptor descriptor;
    Vec3f position_copy;
    Vec3f submit_position;
    s16 indices[10];
    EffectParams params;
    u32 object_type;
    s16 count;
    s16* index;
    void** output;
    int i;

    fn_801CECB4(type, indices);
    fn_80190558(&params);
    params.value24 = value24;
    params.value1C = value1C;
    if (objects != 0) {
        params.flag20 = 1;
    } else {
        params.value06 = value;
    }

    object_type = fn_801D38E8(type);
    count = fn_801CEB2C(type);
    output = objects;
    index = indices;
    for (i = 0; i < count;) {
        f32 angle = lbl_80651038 * i / count;
        descriptor.word = lbl_80651E98;
        descriptor.half = lbl_80651E9C;
        position_copy.x = position->x + lbl_8065103C * fn_80048C2C(angle);
        position_copy.y = position->y + lbl_8065103C * fn_80048C50(angle);
        position_copy.z = lbl_80651040 + position->z;
        params.value04 = *index;
        params.object10 = fn_801D3988(*index, object_type);
        params.angle14 = angle;
        submit_position = position_copy;
        {
            void* effect = fn_80148008(&submit_position, &descriptor, &params,
                                       fn_80190320);
            if (effect != 0) {
                if (objects != 0) {
                    *output = fn_80156938(effect);
                    if (*output != 0) {
                        fn_8017FF1C(*output, 4);
                    }
                }
            } else if (objects != 0) {
                *output = 0;
            }
        }
        index++;
        output++;
        i++;
    }
}
