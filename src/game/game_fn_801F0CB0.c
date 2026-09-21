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

extern s32 lbl_8064D6F8;
extern s32 lbl_8064D738;
extern float lbl_8064C390;
extern u8 lbl_8063BEA0[];
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
extern void fn_80211710(void*, void*, Vec3*);
extern void fn_802117F0(void*, Vec3*, Vec3*);
extern void fn_80211BA0(Vec3*, Vec3*, Vec3*);
extern void fn_80227874(void*, float, float, float, float, float, float);
extern void fn_80227890(void*, float, s32);
extern void fn_80227A10(void*, float, float, s32);
extern void fn_80227AE0(void*, float, float, float);
extern void fn_80227AF0(void*, float, float, float);
extern void fn_80227B0C(void*, float, float, float);
extern void fn_80227BE0(void*, s32*);
extern void fn_80227C08(void*, s32);

typedef struct EmitterSlot {
    u8 data[0x40];
} EmitterSlot;

/* Aim records follow the sixteen emitter slots in the shared pool. */
static inline AimRecord* aim_records(EmitterSlot* pool)
{
    return (AimRecord*)(pool + 16);
}

#pragma use_lmw_stmw on

/* NonMatching: size-exact reconstruction. Reusing the typed emitter pool
 * preserves the emitter-address grouping, but GC/1.3 retains the pool in an
 * extra saved register and schedules the record base before its index.
 * The conversion-bias constants use the existing audited externalization. */
void fn_801F0CB0(u8* source, Vec3* target, void* owner, s32 index, u8 mode,
                 Vec3* color, u8* attributes)
{
    u8* base;
    EmitterSlot* emitterBase;
    void* emitter;
    Vec3 transformed;
    Vec3 direction;
    s32 scale = *(s32*)(source + 0x10);
    float red = lbl_80651394;
    float green = lbl_80651398;
    float blue = lbl_8065139C;

    base = lbl_8063BEA0;
    emitterBase = (EmitterSlot*)(base + 0x258);
    emitter = emitterBase + (index + (lbl_8064D6F8 << 3)) +
              (lbl_8064D738 << 3);

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
            s32 value = *(s32*)(source + 0x0C);
            fn_80227BE0(emitter, &value);
            fn_80227874(emitter, lbl_806513A4 * (float)scale,
                        lbl_80651348, lbl_80651348,
                        red, green, blue);
            fn_80211710(base + 0x1C8, source, &transformed);
            fn_80227AE0(emitter, transformed.x, transformed.y, transformed.z);
        } else {
            s32 value = *(s32*)(source + 0x0C);
            fn_80227BE0(emitter, &value);
            fn_80211710(base + 0x1C8, source, &transformed);
            fn_80227AE0(emitter, transformed.x, transformed.y, transformed.z);

            red = fn_800ED720(*(float*)(attributes + 0) * *(float*)(attributes + 0) +
                              *(float*)(attributes + 4) * *(float*)(attributes + 4) +
                              *(float*)(attributes + 8) * *(float*)(attributes + 8));
            *(float*)(attributes + 0) /= red;
            *(float*)(attributes + 4) /= red;
            *(float*)(attributes + 8) /= red;
            fn_802117F0(base + 0x1C8, (Vec3*)attributes, &transformed);
            fn_80227AF0(emitter, transformed.x, transformed.y, transformed.z);
            fn_80227890(emitter, (float)attributes[0x0E], attributes[0x10]);
            fn_80227A10(emitter, (float)*(u16*)(attributes + 0x0C),
                        lbl_806513A8, attributes[0x0F]);
        }
    } else {
        Vec3 basis = lbl_8023B798;
        Vec3 cross;
        AimRecord* records;

        direction.x = target->x - *(float*)(source + 0);
        direction.y = target->y - *(float*)(source + 4);
        direction.z = target->z - *(float*)(source + 8);
        red = fn_800ED720(direction.x * direction.x +
                          direction.y * direction.y +
                          direction.z * direction.z);
        direction.x /= red;
        direction.y /= red;
        direction.z /= red;
        fn_802117F0(base + 0x1C8, &direction, &transformed);
        {
            s32 value = *(s32*)(source + 0x0C);
            fn_80227BE0(emitter, &value);
        }
        fn_80211BA0(&transformed, &basis, &cross);
        records = aim_records(emitterBase);
        records[index].direction = cross;
        records[index].distance = red;
        records[index].owner = owner;
        fn_80227B0C(emitter, transformed.x, transformed.y, transformed.z);
        fn_80227874(emitter, lbl_80651348, lbl_80651348,
                    lbl_8065134C, lbl_806513AC,
                    lbl_80651348, lbl_806513B0);
    }
    fn_80227C08(emitter, 1 << index);
}
