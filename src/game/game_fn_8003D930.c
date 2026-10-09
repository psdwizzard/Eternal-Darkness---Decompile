typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct ActorInfo {
    u8 pad_00[0x94];
    s32 mode;
    u8 pad_98[0x7];
    u8 kind;
} ActorInfo;

typedef struct SoundSlot {
    s32 id;
    s32 voices[4];
    u32 handles[4];
} SoundSlot;

extern SoundSlot lbl_80303D90[];
extern s32 lbl_8064D18C;
extern const f32 lbl_8064E2C0;

s32 fn_80036D5C(s32);
void fn_80036DA4(s32, s32);
void fn_8003C6B8(s32, u32, s32);
void fn_8003D408(s32);
s32 fn_8003D4F0(s32);
void fn_80066AEC(s32, s32);
u32 fn_8015424C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 fn_80156940(u32);
void fn_801A7744(Vec3 *, u32);
void fn_801AAE68(s32, s32, s32, void *, s32, s32, s32, u16, f32, s32);
s32 fn_80201B54(s32);
ActorInfo *fn_80201B8C(s32);
u32 fn_80201BC8(s32);
s32 fn_80201EB8(s32);
u8 fn_80204578(s32, Vec3 *);

s32 fn_8003D930(s32 object, u32 target) {
    s32 flags;
    u32 owner;
    s32 model;
    s32 useDefault;
    ActorInfo *info;
    s32 slot;
    Vec3 pos;

    useDefault = 1;
    owner = fn_80201BC8(object);
    model = fn_80201B54(object);
    flags = fn_80036D5C(object);
    if (target != 0) {
        fn_801A7744(&pos, target);
        useDefault = fn_80204578(object, &pos) ? 1 : 0;
    }
    fn_80036DA4(object, flags | 4);
    if (lbl_8064D18C != fn_80201EB8(object)) {
        return 0;
    }
    info = fn_80201B8C(object);
    if (info != 0 && info->kind == 3) {
        switch (info->mode) {
        case 3:
        case 4:
            slot = fn_8003D4F0(model);
            fn_801AAE68(1, 0x50, 0, &pos, 2, 2, 0, lbl_8064D18C, lbl_8064E2C0, 0);
            if (lbl_80303D90[slot].handles[0] == 0 &&
                lbl_80303D90[slot].handles[1] == 0 &&
                lbl_80303D90[slot].handles[2] == 0 &&
                lbl_80303D90[slot].handles[3] == 0) {
                lbl_80303D90[slot].handles[0] = fn_8015424C(model, 0, 1, 1, 0, 0, 1, 0x80);
                lbl_80303D90[slot].handles[1] = fn_8015424C(model, 0, 2, 1, 0, 0, 1, 0x40);
                lbl_80303D90[slot].handles[2] = fn_8015424C(model, 0, 3, 1, 0, 0, 1, 0x40);
                lbl_80303D90[slot].handles[3] = fn_8015424C(model, 0, 0, 1, 0, 0, 1, 0x20);
                if (lbl_80303D90[slot].handles[0] != 0) {
                    lbl_80303D90[slot].voices[0] = fn_80156940(lbl_80303D90[slot].handles[0]);
                }
                if (lbl_80303D90[slot].handles[1] != 0) {
                    lbl_80303D90[slot].voices[1] = fn_80156940(lbl_80303D90[slot].handles[1]);
                }
                if (lbl_80303D90[slot].handles[2] != 0) {
                    lbl_80303D90[slot].voices[2] = fn_80156940(lbl_80303D90[slot].handles[2]);
                }
                if (lbl_80303D90[slot].handles[3] != 0) {
                    lbl_80303D90[slot].voices[3] = fn_80156940(lbl_80303D90[slot].handles[3]);
                }
            }
            if (flags & 0x80) {
                fn_8003C6B8(object, owner, model);
            } else if (useDefault) {
                fn_80066AEC(object, 0);
            } else {
                fn_8003D408(object);
            }
            break;
        }
    }
    return 0;
}
