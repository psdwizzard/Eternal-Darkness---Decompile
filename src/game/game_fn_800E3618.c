typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct ObjState {
    u8 pad0[0x5C];
    s32 unk5C;
    u8 pad60[0xF0];
    s16 unk150;
} ObjState;

typedef struct ObjData {
    u8 pad0[0x8C];
    ObjState *state;
    s32 unk90;
} ObjData;

typedef struct ColorSet {
    u8 unk0;
    u8 unk1;
    u8 pad2[6];
} ColorSet;

typedef struct Colors {
    u8 pad0[0x2A];
    ColorSet set[2];
} Colors;

typedef struct Entry {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Entry;

extern Colors *fn_80072354(s32);
extern void *fn_800C1D54(void);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern void fn_801287C4(void *, void *, u32, u32);
extern void fn_80128C28(void *, u32, u32);
extern void fn_80128C44(void *, u32, u32);
extern u8 fn_80128EE4(void *);
extern void fn_801292E0(void *, s32 *, s32 *);
extern s32 fn_80129334(void *, s32, s32 *, s32);
extern u8 *fn_801294DC(void *, int, int, int);
extern float fn_8012B750(void *);
extern float fn_8012B7D0(const void *, const void *);
extern void fn_8017A12C(float *, float, float);
extern void *fn_801A717C(void);
extern void fn_801A7460(void *, u32);
extern void fn_801A7478(void *, u32);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern u32 fn_801A74C8(void *, u32);
extern void fn_801A7518(void *, s16);
extern void fn_801A7538(void *, u16);
extern void fn_801A7550(void *, u32);
extern void fn_801A7558(void *, u32);
extern u32 fn_801A7560(void *, u32);
extern void fn_801A764C(void *, Vec3 *);
extern void fn_801A7680(void *, u32);
extern void *fn_80201814(s32);
extern s32 fn_80201B54(s32 *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201B94(u8 *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C24(void *);
extern void *fn_80201C48(void *);
extern void fn_80201D14(void *, u8);
extern void fn_80201D2C(void *, s32);

extern s32 fn_8003B8A0(void *, void *);
extern s32 fn_8003BD48(void *, void *);
extern s32 fn_800C3ADC(void *, void *);
extern s32 fn_80204230(s32, s32);
extern s32 fn_802042A4(s32, s32);

extern f32 lbl_8064F678;
extern f32 lbl_8064F67C;

/* A direction may use -1 when no animation is available for it. */
static inline void select_direction_animation(s32 *type, f32 angle,
                                              s32 left, s32 right, s32 forward)
{
    if (angle < lbl_8064F678) {
        *type = left;
    } else if (angle > lbl_8064F67C) {
        *type = right;
    } else {
        *type = forward;
    }
}

s32 fn_800E3618(void *self, void *obj) {
    ObjData *data;
    void *owner;
    u8 flags;
    ObjState *state;
    s32 id;
    s32 param;
    void *entry;
    void *src;
    s32 type;
    void *anim;
    /* Callback queues store the effect address as a 32-bit payload. */
    u32 fx;
    Colors *colors;
    s32 off;
    s32 i;
    s32 frame;
    f32 angle;
    s32 entries;
    s32 count;
    Vec3 pos;
    Vec3 targetPos;
    Vec3 tmp;
    Vec3 tmp2;

    data = fn_80201B8C(self);
    owner = fn_80201B94(self);
    fn_8011F114(&tmp, obj);
    pos = tmp;
    flags = fn_80128EE4(obj);
    id = (s32)fn_80201C48(owner);
    param = fn_80201B54(self);
    state = data->state;
    state->unk150 = 0;
    if (flags & 0x20) {
        goto fail;
    }
    entry = fn_80201814(id);
    if (entry == 0) {
        goto fail;
    }
    src = fn_80201BC8(entry);
    fn_8011F114(&tmp2, src);
    type = 4;
    targetPos = tmp2;
    if (state->unk5C != 0) {
        Vec3 target = targetPos;
        f32 heading = fn_8012B7D0(obj, &target);
        fn_8017A12C(&angle, fn_8012B750(obj), heading);
        select_direction_animation(&type, angle, 4, 5, 6);
    }
    /* Retain the unavailable-direction guard used by the retail caller, even
     * though this action supplies an animation for every direction. */
    if (type == -1) {
        goto fail;
    }
    anim = fn_801294DC(obj, type, 0x30, 6);
    if (anim == 0) {
        goto fail;
    }
    fx = (u32)fn_801A717C();
    colors = fn_80072354(data->unk90);
    fn_801A7460((void *)fx, type);
    fn_801A74A0((void *)fx, param);
    fn_801A74A8((void *)fx, id);
    fn_801A74C8((void *)fx, 1);
    fn_801A7560((void *)fx, 0xA44);
    off = type != 4;
    fn_801A7538((void *)fx, colors->set[off].unk1);
    fn_801A7518((void *)fx, colors->set[off].unk0);
    fn_801A7550((void *)fx, 0xC);
    fn_801A7558((void *)fx, 7);
    fn_801A764C((void *)fx, &pos);
    fn_801292E0(obj, &count, &entries);
    for (i = 0; i < count; i++) {
        Entry *e = &((Entry *)entries)[i];
        switch (e->unk4) {
        case 1:
            frame = e->unk0 >> 17;
            fn_801287C4(anim, fn_8003B8A0, fx, frame - 2);
            fn_801287C4(anim, fn_8003BD48, fx, frame - 1);
            fn_801287C4(anim, fn_8003BD48, fx, frame);
            fn_801287C4(anim, fn_8003BD48, fx, frame + 1);
            if (state->unk5C != 0 && (entry = fn_80201814(state->unk5C)) != 0) {
                s32 last;
                u32 link = (u32)fn_80201C24(entry);
                fn_801A7680((void *)fx, link);
                fn_801A7478((void *)fx, (u32)fn_800C1D54());
                fn_80129334(obj, 1, &last, -1);
                fn_801287C4(anim, fn_800C3ADC, fx, last - 1);
            }
            break;
        }
    }
    fn_80128C28(anim, (u32)fn_80204230, fx);
    fn_80128C44(anim, (u32)fn_802042A4, fx);
    fn_80201D2C(self, 6);
    fn_80201D14(self, 1);
    return 1;
fail:
    return 0;
}
