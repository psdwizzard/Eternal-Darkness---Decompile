typedef signed long s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct AimRecord {
    Vec3 direction;
    u8 pad0C[0x0C];
    void* owner;
    float distance;
} AimRecord;

typedef struct EffectRec {
    Vec3 pos;
    s32 value;
    s32 intensity;
} EffectRec;

typedef struct EffectAttributes {
    Vec3 direction;
    u16 field_0C;
    u8 field_0E;
    u8 field_0F;
    u8 field_10;
} EffectAttributes;

extern s32 lbl_8064D6F8;
extern s32 lbl_8064D738;
extern float lbl_8064C390;
extern Vec3 lbl_8023B798;
extern float lbl_80651394;
extern float lbl_80651398;
extern float lbl_8065139C;
extern float lbl_806513A0;
extern float lbl_806513A4;
extern float lbl_806513A8;
extern float lbl_806513AC;
extern float lbl_806513B0;
extern float lbl_80651348;
extern float lbl_8065134C;

extern float fn_800ED720(float);
extern void PSMTXMultVec(void*, void*, Vec3*);
extern void PSMTXMultVecSR(void*, Vec3*, Vec3*);
extern void C_VECHalfAngle(Vec3*, Vec3*, Vec3*);
extern void GXInitLightAttn(void*, float, float, float, float, float, float);
extern void GXInitLightSpot(void*, float, s32);
extern void GXInitLightDistAttn(void*, float, float, s32);
extern void GXInitLightPos(void*, float, float, float);
extern void GXInitLightDir(void*, float, float, float);
extern void GXInitSpecularDir(void*, float, float, float);
extern void GXInitLightColor(void*, s32*);
extern void GXLoadLightObjImm(void*, s32);

typedef struct EmitterSlot {
    u8 data[0x40];
} EmitterSlot;

static u8 effect_8063BEA0[0x20] = {0};
static u8 effect_8063BEC0[0x5C] = {0};
static float effect_8063BF1C[3] = {0};
static float effect_8063BF28[16] = {0};
static u8 effect_8063BF68[0xC0] = {0};
static u8 effect_8063C028[0x40] = {0};
static u8 effect_matrix[0x30] = {0};
static u8 effect_8063C098[0x30] = {0};
static u8 effect_8063C0C8[0x30] = {0};
static EmitterSlot effect_emitters[2][8] = {0};
static AimRecord effect_records[8] = {0};

#pragma use_lmw_stmw on

void fn_801F0CB0(EffectRec* source, Vec3* target, void* owner, s32 index, u8 mode,
                 Vec3* color, EffectAttributes* attributes)
{
    Vec3 transformed;
    float red;
    float green;
    s32 scale;
    Vec3 direction;
    void* emitter;
    float blue;

    scale = source->intensity;
    red = lbl_80651394;
    green = lbl_80651398;
    blue = lbl_8065139C;

    emitter = &effect_emitters[lbl_8064D738][index + lbl_8064D6F8 * 8];

    if (index == 0) {
        lbl_8064C390 -= lbl_806513A0;
    }
    if (color != 0) {
        red = color->x;
        green = color->y;
        blue = color->z;
    }

    if (mode == 0) {
        if (attributes == 0) {
            s32 value = source->value;
            GXInitLightColor(emitter, &value);
            GXInitLightAttn(emitter, lbl_806513A4 * (float)scale,
                        lbl_80651348, lbl_80651348,
                        red, green, blue);
            PSMTXMultVec(effect_matrix, source, &transformed);
            GXInitLightPos(emitter, transformed.x, transformed.y, transformed.z);
        } else {
            s32 value = source->value;
            GXInitLightColor(emitter, &value);
            PSMTXMultVec(effect_matrix, source, &transformed);
            GXInitLightPos(emitter, transformed.x, transformed.y, transformed.z);

            red = fn_800ED720(attributes->direction.x * attributes->direction.x +
                              attributes->direction.y * attributes->direction.y +
                              attributes->direction.z * attributes->direction.z);
            attributes->direction.x /= red;
            attributes->direction.y /= red;
            attributes->direction.z /= red;
            PSMTXMultVecSR(effect_matrix, &attributes->direction, &transformed);
            GXInitLightDir(emitter, transformed.x, transformed.y, transformed.z);
            GXInitLightSpot(emitter, (float)attributes->field_0E, attributes->field_10);
            GXInitLightDistAttn(emitter, (float)attributes->field_0C,
                        lbl_806513A8, attributes->field_0F);
        }
    } else {
        Vec3 basis = lbl_8023B798;
        Vec3 cross;

        direction.x = target->x - source->pos.x;
        direction.y = target->y - source->pos.y;
        direction.z = target->z - source->pos.z;
        red = fn_800ED720(direction.x * direction.x +
                          direction.y * direction.y +
                          direction.z * direction.z);
        direction.x /= red;
        direction.y /= red;
        direction.z /= red;
        PSMTXMultVecSR(effect_matrix, &direction, &transformed);
        {
            s32 value = source->value;
            GXInitLightColor(emitter, &value);
        }
        C_VECHalfAngle(&transformed, &basis, &cross);
        effect_records[index].direction = cross;
        effect_records[index].distance = red;
        effect_records[index].owner = owner;
        GXInitSpecularDir(emitter, transformed.x, transformed.y, transformed.z);
        GXInitLightAttn(emitter, lbl_80651348, lbl_80651348,
                    lbl_8065134C, lbl_806513AC,
                    lbl_80651348, lbl_806513B0);
    }
    GXLoadLightObjImm(emitter, 1 << index);
}
