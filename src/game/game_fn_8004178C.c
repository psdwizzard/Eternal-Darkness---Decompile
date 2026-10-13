typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct ModelInfo {
    u8 pad0[0x4];
    s32 handle;
    u8 pad8;
    u8 flags;
} ModelInfo;

typedef struct ActorInfo {
    u8 pad0[0x4];
    ModelInfo *model;
    u8 pad8[0x9C - 0x8];
    s16 timer;
} ActorInfo;

typedef struct ActorState {
    u8 pad0[0x14A];
    s16 turnRate;
} ActorState;

extern int fn_80200C10(void *event);
extern void *fn_80201BC8(void *context);
extern ActorInfo *fn_80201B8C(void *context);
extern int fn_80201B54(void *context);
extern int fn_80201EB8(void *context);
extern void fn_8011F114(Vec3 *pos, void *object);
extern ActorState *fn_80036D38(void *context);
extern void fn_80067858(int id);
extern unsigned int fn_8011FA8C(void *object, int set, int clear);
extern void *fn_801294DC(void *object, int type, int value, int flags);
extern void fn_80201D2C(void *context, int value);
extern void fn_80201D14(void *context, int value);
extern int fn_8011EB04(void *object);
extern void fn_80128754(void *object, int value);
extern int fn_8011FF38(void);
extern s32 fn_801AAE68(u16 id, u8 a, u8 b, f32 scale, Vec3 *pos, signed char c,
                       u8 d, u8 e, u16 room, u32 f);
extern void fn_8012B324(void *object);
extern void fn_80201D34(void *context, int value);
extern void fn_80201D1C(void *context, int value);
extern void fn_801E8328(int type, void *context);
extern s32 fn_800359A0(void *context, s32 value);
extern void *fn_80201B94(void *context);
extern int fn_80201C50(void);
extern void fn_802045AC(void *context, Vec3 *pos);
extern int fn_80179064(int x1, int y1, int x2, int y2);
extern unsigned long long fn_8020123C(int type, int source, int target, int value);
extern int fn_800CB254(void *context, int a, int b, int c, int d);
extern int fn_8011FAEC(void *object);
extern void fn_8016B400(int handle, int id, int value);
extern void fn_8012B344(void *object);
extern void fn_80128C44(void *object, void *callback, u32 value);
extern void fn_80128C28(void *object, void *callback, u32 value);
extern void fn_800073D8(int value);
extern void fn_8011FADC(void *object, int flags);
extern void fn_8020104C(int type, int source, int target, int value, f32 scale);
extern void fn_80204810();

extern s32 lbl_8064D5A8;
extern s32 lbl_8064D18C;
extern const f32 lbl_8064E2C0;
extern const f32 lbl_8064E328;

s32 fn_8004178C(void *context, s32 type, void *event, s32 *result)
{
    s32 kind;
    void *object;
    ActorInfo *info;
    s32 id;
    s32 owner;
    Vec3 pos;
    ActorState *state;
    s32 tick;
    Vec3 targetPos;

    kind = fn_80200C10(event);
    object = fn_80201BC8(context);
    info = fn_80201B8C(context);
    id = fn_80201B54(context);
    owner = fn_80201EB8(context);
    fn_8011F114(&pos, object);
    state = fn_80036D38(context);
    tick = lbl_8064D5A8 + info->timer;

    if (type == 0) {
        if (kind == 1) {
            fn_80067858(id);
            fn_8011FA8C(object, 0xC0, 0);
            if (lbl_8064D18C == fn_80201EB8(context)) {
                fn_801294DC(object, 0x4F, 0x25, 0xA);
            }
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            if (fn_8011EB04(object) == 0x89) {
                fn_80128754(object, -1);
            }
            return 1;
        }
        if (kind == 0xC9) {
            if (fn_8011FF38() != 0) {
                fn_8011FA8C(object, 0, 0x20000000);
                fn_801AAE68(0x1F1, 0x64, 0, lbl_8064E2C0, &pos, 2, 2, 0,
                            (u16)lbl_8064D18C, 0);
            }
            return 1;
        }
        if (kind == 0x3E) {
            fn_801294DC(object, 0x4F, 0x25, 0xA);
            return 1;
        }
        if (kind == 0x39) {
            fn_8012B324(object);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
    } else if (type == 1) {
        if (kind == 3) {
            s16 saved = state->turnRate;
            int status;

            state->turnRate = 0x168;
            if (fn_800359A0(context, 0) != 0) {
                fn_80201B94(context);
                status = fn_80201C50();
                if (!(status != 0 && status != -1 && status != 0xFFFF &&
                      status <= 2000)) {
                    state->turnRate = saved;
                    fn_802045AC(context, &targetPos);
                    if (fn_80179064((int)pos.x, (int)pos.y, (int)targetPos.x,
                                    (int)targetPos.y) < 1000) {
                        fn_8020123C(0x18, id, id, 0);
                    }
                }
            }
            state->turnRate = saved;
            return 1;
        }
        if (kind == 0x18) {
            s32 busy = fn_800CB254(context, 0x32, 0, lbl_8064D18C, 1);
            int status;

            fn_80201B94(context);
            status = fn_80201C50();
            if (busy == 0 && owner == lbl_8064D18C) {
                int flags = fn_8011FAEC(object);
                ModelInfo *model = info->model;
                void *child;

                if (model != 0 && model->handle != 0) {
                    fn_8016B400(model->handle, id, 0);
                }
                fn_8012B344(object);
                child = fn_801294DC(object, 0x29, 0x20, 8);
                if (child != 0) {
                    fn_80128C44(child, fn_80204810, (id << 8) | 7);
                    fn_80128C28(child, fn_80204810, (id << 8) | 0x38);
                    info->model->flags |= 8;
                    fn_80201D34(context, 4);
                    fn_80201D1C(context, 1);
                } else {
                    fn_800073D8(lbl_8064D18C);
                }
                fn_8011FADC(object, flags | 0xC0);
            } else if (status != 0 && status != -1 && status != 0xFFFF &&
                       status < 2000) {
                fn_8020104C(0x18, id, id, 0, lbl_8064E328);
            }
            return 1;
        }
    } else if (type == 0x21) {
        if (kind == 3) {
            if ((tick & 7) == 0) {
                fn_800359A0(context, 0);
            }
            return 1;
        }
        if (kind == 0x38) {
            fn_80201D34(context, 4);
            fn_80201D1C(context, 1);
            return 1;
        }
        if (kind == 0x3B) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x3D) {
            if (owner == 0x9D) {
                fn_8012B344(object);
                fn_80201D34(context, 4);
                fn_80201D1C(context, 1);
            }
            return 1;
        }
        if (kind == 0x3E) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
