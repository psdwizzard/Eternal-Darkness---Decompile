typedef signed long s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

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

#pragma use_lmw_stmw on

void fn_801F0CB0(u8* source, Vec3* target, void* owner, s32 index, u8 mode,
                 Vec3* color, u8* attributes)
{
    void* emitter;
    Vec3 transformed;
    Vec3 direction;
    Vec3 basis = lbl_8023B798;
    float red = lbl_80651394;
    float green = lbl_80651398;
    float blue = lbl_8065139C;
    s32 value;

    emitter = lbl_8063BEA0 + 0x258 +
              (lbl_8064D738 << 9) + ((index + (lbl_8064D6F8 << 3)) << 6);

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
            value = *(s32*)(source + 0x0C);
            fn_80227BE0(emitter, &value);
            fn_80227874(emitter, lbl_806513A4,
                        lbl_806513A4, red, green, blue,
                        lbl_806513A8 * (float)*(s32*)(source + 0x10));
            fn_80211710(lbl_8063BEA0 + 0x1C8, source, &transformed);
            fn_80227AE0(emitter, transformed.x, transformed.y, transformed.z);
        } else {
            value = *(s32*)(source + 0x0C);
            fn_80227BE0(emitter, &value);
            fn_80211710(lbl_8063BEA0 + 0x1C8, source, &transformed);
            fn_80227AE0(emitter, transformed.x, transformed.y, transformed.z);

            direction.x = *(float*)(attributes + 0);
            direction.y = *(float*)(attributes + 4);
            direction.z = *(float*)(attributes + 8);
            red = fn_800ED720(direction.x * direction.x +
                              direction.y * direction.y +
                              direction.z * direction.z);
            direction.x /= red;
            direction.y /= red;
            direction.z /= red;
            fn_802117F0(lbl_8063BEA0 + 0x1C8, &direction, &transformed);
            fn_80227AF0(emitter, transformed.x, transformed.y, transformed.z);
            fn_80227890(emitter, (float)attributes[0x0E], attributes[0x10]);
            fn_80227A10(emitter, (float)*(u16*)(attributes + 0x0C),
                        lbl_806513AC, attributes[0x0F]);
        }
    } else {
        direction.x = target->x - *(float*)(source + 0);
        direction.y = target->y - *(float*)(source + 4);
        direction.z = target->z - *(float*)(source + 8);
        red = fn_800ED720(direction.x * direction.x +
                          direction.y * direction.y +
                          direction.z * direction.z);
        direction.x /= red;
        direction.y /= red;
        direction.z /= red;
        fn_802117F0(lbl_8063BEA0 + 0x1C8, &direction, &transformed);
        value = *(s32*)(source + 0x0C);
        fn_80227BE0(emitter, &value);
        fn_80211BA0(&transformed, &basis, &direction);
        *(Vec3*)(lbl_8063BEA0 + 0x658 + (index << 5)) = direction;
        *(float*)(lbl_8063BEA0 + 0x658 + (index << 5) + 0x1C) = red;
        *(void**)(lbl_8063BEA0 + 0x658 + (index << 5) + 0x18) = owner;
        fn_80227B0C(emitter, transformed.x, transformed.y, transformed.z);
        fn_80227874(emitter, lbl_806513A4, lbl_806513A4,
                    lbl_806513B0, lbl_806513A4, lbl_80651394, lbl_80651398);
    }
    fn_80227C08(emitter, 1 << index);
}
