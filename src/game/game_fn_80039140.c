typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
#define NULL ((void *)0)

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Segment {
    u8 data[0x28];
} Segment;

typedef struct ObjState {
    u8 pad[0x9E];
    u8 unk9E;
    u8 unk9F;
} ObjState;

extern void fn_80046E98(int);
extern void *fn_8004914C(int);
extern int fn_8011EB04(void *);
extern int fn_8011F130(void *);
extern void fn_8012C478(void *, int, int);
extern u32 fn_80135D80(Vec3 *, Vec3 *, Vec3 *, Vec3 *, void *, void *, int, int, f32);
extern void fn_8013F4D0(Segment *, Vec3 *, Vec3 *);
extern u32 fn_8014317C(Segment *, Vec3 *, void *, int, int);
extern u32 fn_801436E0(void *, void *, int);
extern void fn_801A74B0(int, int);
extern u32 fn_801A74C0(int);
extern u32 fn_801A7570(int);
extern void fn_801A7588(int, u32);
extern void fn_801A7688(int, int, Vec3 *);
extern u8 fn_801A76B0(int);
extern int fn_801A7770(int);
extern u64 fn_8020123C(int, int, int, int);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern int fn_80201B64(void *);
extern ObjState *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);

extern f32 lbl_8064E240;

int fn_80039140(void *source, void *target, int ctx) {
    u8 hitInfo[0x2C];
    Vec3 corners[4];
    Segment seg;
    Vec3 hitPos;
    int result;
    int extra;
    void *sourceObj;
    void *targetObj;
    void *special;
    int sourceId;
    int targetId;
    u32 mode;
    ObjState *sourceState;
    ObjState *targetState;
    u32 flags;
    int i;
    Vec3 *corner;
    u32 hit;
    int slot;
    int isBoss;
    int flag;
    u8 kind;
    int srcId;
    int playerId;
    int targetType;

    extra = 0;
    result = 0;
    sourceId = fn_80201B54(source);
    fn_801A74C0(ctx);
    special = fn_8004914C(ctx);
    if (target != NULL && (sourceObj = fn_80201BC8(source)) != NULL &&
        (targetObj = fn_80201BC8(target)) != NULL) {
        kind = fn_801A76B0(ctx);
        srcId = fn_80201B54(source);
        playerId = fn_80201B44();
        targetType = fn_80201B64(target);
        targetId = fn_80201B54(target);
        if (kind == 0x10 && playerId == srcId && (fn_801A74C0(ctx) & 4) && targetType != 0x21) {
            fn_801A7588(ctx, 2);
            result = fn_8020123C(0xB, fn_80201B54(source), fn_80201B54(target), ctx) & 0xFFFFFFFF;
        } else {
            targetState = fn_80201B8C(target);
            sourceState = fn_80201B8C(source);
            hit = 0;
            fn_801A7688(ctx, 0, &corners[0]);
            fn_801A7688(ctx, 1, &corners[1]);
            fn_801A7688(ctx, 2, &corners[3]);
            fn_801A7688(ctx, 3, &corners[2]);
            mode = fn_80135D80(&corners[0], &corners[1], &corners[3], &corners[2], targetObj, hitInfo,
                               1, 1, lbl_8064E240);
            flags = fn_801A7570(ctx) & 0x100000;
            if (flags != 0) {
                i = 0;
                if (mode != 0) {
                    extra = fn_8011F130(targetObj);
                }
                for (corner = &corners[0]; i < 3 && hit == 0; corner++, i++) {
                    fn_8013F4D0(&seg, corner, &corners[i + 1]);
                    hit = fn_8014317C(&seg, &hitPos, sourceObj, extra, 0);
                }
                if (hit == 0) {
                    fn_8013F4D0(&seg, &corners[3], &corners[0]);
                    hit = fn_8014317C(&seg, &hitPos, sourceObj, extra, 0);
                }
                if (hit != 0) {
                    result |= 0x40;
                }
            }

            if (mode != 0) {
                slot = fn_801A7770(ctx);
                if (hit == 0 && flags != 0) {
                    hit = fn_801436E0(sourceObj, targetObj, 1);
                    if (hit != 0) {
                        result |= 0x40;
                    }
                }
                if (hit == 0) {
                    if (slot != -1) {
                        flag = 0;
                        isBoss = flag;
                        if (special != NULL && fn_8011EB04(special) == 0xD2) {
                            isBoss = 1;
                        }
                        if (isBoss && slot == 0) {
                            flag = 1;
                        }
                        fn_801A7588(ctx, 1 << slot);
                        result = fn_8020123C(0xB, fn_80201B54(source), fn_80201B54(target), ctx) &
                                 0xFFFFFFFF;
                        if (result != 0 && targetState != NULL && targetState->unk9E == 2 &&
                            sourceState != NULL && sourceState->unk9F == 0x28) {
                            fn_8012C478(targetObj, 0xF, 0);
                            fn_80046E98(targetId);
                        }
                        if (result != 0 && flag != 0) {
                            result |= 0x28;
                        }
                        if (result == 0) {
                            fn_801A7588(ctx, mode);
                            result = fn_8020123C(0xB, sourceId, targetId, ctx) & 0xFFFFFFFF;
                            if (result != 0 && flag != 0) {
                                result |= 0x28;
                            }
                        }
                    } else {
                        if (mode == 0x8000) {
                            mode = 2;
                        }
                        if (mode & 0x8000) {
                            mode = mode & ~0x8000;
                            mode |= 2;
                        }
                        fn_801A7588(ctx, mode);
                        result = fn_8020123C(0xB, sourceId, targetId, ctx) & 0xFFFFFFFF;
                    }
                }
            }
        }
        if (result != 0) {
            fn_801A74B0(ctx, targetId);
        }
    }
    return result;
}
