typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Target {
    /* 0x000 */ u32 flags;
    /* 0x004 */ char unk4[0x94 - 0x4];
    /* 0x094 */ Vec3 pos;
    /* 0x0A0 */ char unkA0[0x150 - 0xA0];
    /* 0x150 */ s16 health;
} Target;

typedef struct ObjInfo {
    /* 0x00 */ char unk0[0x2C];
    /* 0x2C */ u32 flags;
} ObjInfo;

typedef struct Context {
    /* 0x00 */ char unk0[0x68];
    /* 0x68 */ ObjInfo *info;
    /* 0x6C */ char unk6C[0x9C - 0x6C];
    /* 0x9C */ s16 timerOffset;
} Context;

extern Context *fn_80201B8C(void);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern u64 fn_8020123C(int, int, int, int);
extern s32 fn_80093264(void);
extern void fn_800931D0(void *, int, Target *);
extern s32 fn_80092C30(void *, ObjInfo *);
extern void fn_80093148(void *, int);
extern void fn_80094DD0(void *, void *, int);
extern void fn_80092FA4(void *, int, Target *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_8012FE10(void *, s32, Vec3 *);
extern s32 fn_8012FF34(void *, Vec3 *, s32, s32);
extern void fn_801302BC(void *, s32);
extern f32 fn_8012B7D0(void *, Vec3);
extern f32 fn_8012B750(void *);
extern void fn_8017A12C(f32 *, f32, f32);

extern void *lbl_8064C4E4;
extern s32 lbl_8064C55C;
extern s32 lbl_8064D5A8;
extern f32 lbl_8064EC7C;
extern f32 lbl_8064ECCC;
extern f32 lbl_8064ECD0;

s32 fn_80095954(void *object, void *actor, int id, Target *target, int arg4) {
    Context *ctx;
    ObjInfo *info;
    s32 result = 1;
    s32 flag400;
    s32 flag800;
    s32 timer;
    u32 targetFlags;
    u32 targetFlag800;
    f32 angle;
    f32 absAngle;
    f32 turn;

    ctx = fn_80201B8C();
    info = ctx->info;
    flag400 = info->flags & 0x400;
    flag800 = info->flags & 0x800;
    timer = lbl_8064D5A8 + ctx->timerOffset;

    if (lbl_8064C55C != 0) {
        if (fn_80093264() != 0) {
            fn_8020123C(0xA7, id, id, 0);
            result = 1;
        } else {
            result = 0;
        }
    } else {
        fn_800931D0(object, id, target);
        if (fn_80092C30(object, info) != 0) {
            fn_8020123C(0xA7, id, id, 0);
        } else {
            targetFlags = target->flags;
            targetFlag800 = targetFlags & 0x800;
            if (targetFlag800 != 0 && (targetFlags & 0x80) && target->health <= 0) {
                fn_80093148(object, id);
            } else if (targetFlag800 != 0 && target->health <= 0) {
                fn_80093148(object, id);
            } else {
                fn_80094DD0(object, actor, arg4);
                if (flag400 != 0 || flag800 != 0) {
                    Vec3 pos;
                    Vec3 checkPos;
                    Vec3 tmp;

                    fn_8011F114(&tmp, lbl_8064C4E4);
                    checkPos = tmp;
                    pos = tmp;
                    checkPos.z += lbl_8064ECCC;
                    fn_8012FE10(lbl_8064C4E4, 0, &checkPos);
                    if (fn_8012FF34(actor, &checkPos, 4, 4) != 0) {
                        fn_801302BC(actor, 5);
                    }
                    if (lbl_8064D5A8 % 180 == 0 && !(info->flags & 0x1000)) {
                        turn = fn_8012B7D0(actor, pos);
                        fn_8017A12C(&angle, fn_8012B750(actor), turn);
                        absAngle = angle;
                        if (absAngle < lbl_8064EC7C) {
                            absAngle = -absAngle;
                        }
                        if (absAngle > lbl_8064ECD0) {
                            target->pos = pos;
                            fn_80201D2C(object, 0x15);
                            fn_80201D14(object, 1);
                        } else if (!(timer & 0x1FF)) {
                            fn_8020123C(0xBA, id, id, 0);
                        }
                    }
                } else {
                    fn_80092FA4(object, id, target);
                }
            }
        }
    }
    return result;
}
