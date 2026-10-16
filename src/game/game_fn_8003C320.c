typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;
#define NULL ((void *)0)

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct ObjData {
    u8 pad0[0x108];
    s16 unk108;
} ObjData;

typedef struct ObjSub {
    ObjData *data;
    u8 pad4[5];
    u8 flags;
} ObjSub;

typedef struct ObjInfo {
    u8 pad0[4];
    ObjSub *sub;
    u8 pad8[0x94 - 0x8];
    s32 state;
    u8 pad98[0x9E - 0x98];
    u8 unk9E;
    u8 unk9F;
} ObjInfo;

typedef struct Triple {
    s32 a, b, c;
} Triple;

extern void *fn_80201B8C(u8 *);
extern void *fn_80201BC8(void *);
extern s32 fn_80201B54(s32 *);
extern void fn_8011F114(Vec3 *, Vec3 *);
typedef struct Object80201EB8 Object80201EB8;
extern int fn_80201EB8(Object80201EB8 *);
extern s32 fn_80200C20(s32 *);
typedef struct Entry80201814 Entry80201814;
extern Entry80201814 *fn_80201814(s32);
extern void *fn_80036D5C(void *);
extern int fn_801E8328(u32, u32);
typedef struct Object80201D34 Object80201D34;
extern void fn_80201D34(Object80201D34 *, s32);
typedef struct Object80201D1C Object80201D1C;
extern void fn_80201D1C(Object80201D1C *, u8);
typedef struct Object80201D2C Object80201D2C;
extern void fn_80201D2C(Object80201D2C *, s32);
typedef struct Object80201D14 Object80201D14;
extern void fn_80201D14(Object80201D14 *, u8);
extern void fn_8003C6B8(void *, void *, s32);
extern s32 fn_80066D04(s32, s32);
extern s32 fn_8003D69C(s32);
extern s32 fn_8006A4D4(s32);
extern void *fn_80200C38(void **);
typedef struct Data Data;
extern u32 fn_801A74C0(Data *);
extern void *fn_80205868(void *, int, void *, u32);
extern int fn_80201B5C(int *);
extern u8 *fn_801294DC(void *, int, int, int);
extern int fn_800389E0(void *, int, s16, int);
typedef struct Runtime Runtime;
extern void fn_80128C28(Runtime *, u32, u32);
extern int fn_801AC908(u32, void *, u8);
extern int fn_801AAE68(u16, u8, u8, f32, Vec3 *, signed char, u8, u8, u16, u32);
extern void fn_80067BAC(void *);
extern void fn_80067C20(void *);
extern void fn_80067EB8(void *);
extern void fn_80068074();
extern int fn_800CA2C8(void *);
extern void fn_80201138(int, void *, int, int, int, f32);
extern s32 fn_800683E4(void *, s32);
extern s32 fn_8003CB6C(void *, s32);

extern Triple lbl_80238DD0;
extern s32 lbl_8064C548;
extern s32 lbl_8064C5AC;
extern s32 lbl_8064D18C;
extern const f32 lbl_8064E284;
extern const f32 lbl_8064E288;
extern const f32 lbl_8064E28C;

void fn_8003C320(void *obj, void *arg1) {
    Vec3 pos;
    Triple tmp;
    ObjInfo *info;
    void *other;
    void *res;
    s32 ctx;
    ObjInfo *otherInfo;
    void *task;
    int id;
    int ok;
    u32 flags;
    f32 f;

    info = fn_80201B8C(obj);
    res = fn_80201BC8(obj);
    ctx = fn_80201B54(obj);
    fn_8011F114(&pos, res);
    id = fn_80201EB8(obj);
    other = fn_80201814(fn_80200C20(arg1));
    if (other != NULL) {
        otherInfo = fn_80201B8C((u8 *)other);
    } else {
        otherInfo = NULL;
    }
    flags = (u32)fn_80036D5C(obj);
    if (id != lbl_8064D18C) {
        fn_801E8328(2, (u32)obj);
        fn_80201D34(obj, 0);
        fn_80201D1C(obj, 1);
        return;
    }
    if (flags & 0x80) {
        fn_8003C6B8(obj, res, ctx);
        return;
    }
    switch (info->state) {
    case 2:
        if (fn_80066D04((s32)obj, 0) != 0 && fn_80066D04((s32)obj, 1) != 0 &&
            fn_8003D69C(ctx) == 0 && fn_8006A4D4((s32)obj) != 0) {
            ok = 1;
            if (lbl_8064D18C == 0xD0 && info->unk9E == 1) {
                ok = 0;
            } else if (info->sub != NULL && (info->sub->flags & 2)) {
                ok = 0;
            } else if (otherInfo != NULL && otherInfo->unk9F == 7) {
                void *item = fn_80200C38(arg1);
                ok = 0;
                tmp = lbl_80238DD0;
                if (item != NULL && !(fn_801A74C0(item) & 0x200000)) {
                    fn_80205868(res, 0, &tmp, 0x2000);
                }
            } else if (other != NULL && fn_80201B5C(other) == 0x27) {
                ok = 0;
            }
            if (ok) {
                task = fn_801294DC(res, 0x2B, 0x24, 0xA);
                if (task != NULL) {
                    fn_800389E0(obj, 0, 1, 1);
                    fn_80128C28(task, (u32)fn_800683E4, ctx);
                    if (fn_801AC908(lbl_8064C5AC, &pos, 100) == 0) {
                        lbl_8064C5AC = fn_801AAE68(0x4B, 100, 0, lbl_8064E284, &pos,
                                                   1, 2, 0, lbl_8064D18C, 0);
                    }
                    lbl_8064C548 = 0;
                    fn_80067BAC(obj);
                    fn_80067C20(obj);
                    fn_80067EB8(obj);
                    fn_80068074(obj);
                    fn_800CA2C8(obj);
                    fn_80201D34(obj, 0x1C);
                    fn_80201D1C(obj, 1);
                    info->sub->data->unk108 = 300;
                }
                return;
            }
        }
        break;
    }
    task = fn_801294DC(res, 0x18, 0x20, 0xA);
    if (task != NULL) {
        fn_80128C28(task, (u32)fn_8003CB6C, ctx);
        fn_800389E0(obj, 0, 0, 1);
        switch (lbl_8064D18C) {
        case 0x199:
        case 0xFB:
            f = lbl_8064E288;
            break;
        default:
            f = lbl_8064E28C;
            break;
        }
        fn_80201138(0x11, obj, 8, -1, 0, f);
        fn_80201D2C(obj, 8);
        fn_80201D14(obj, 1);
    }
}
