typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef int s32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct HitResult {
    u8 pad00[8];
    Vec3 position;
    Vec3 normal;
} HitResult;
typedef struct EffectState {
    u8 pad00[4];
    u32 owner;
    u8 pad08[0x14];
    s16 finished;
    u8 pad1E[4];
    u16 status;
    u8 pad24[2];
    u16 timer;
    u8 pad28[8];
    u32 flags;
} EffectState;

extern u8 lbl_8064B590[4];
extern EffectState *fn_801FD6F4(void *);
extern s32 fn_8015E4E8(EffectState *);
extern s32 fn_801FE52C(void *);
extern void *fn_80201814();
extern void *fn_80155DB4();
extern void* fn_80201C24();
extern void *fn_80201BC8();
extern s32 fn_8011F6A4(void *, s32, s32, s32, HitResult *, s32);
extern void fn_801FE890(void *, Vec3 *);
extern Vec3 *fn_8011F130(void *);
extern u8 fn_80157AB8(void *);
extern void fn_801FD80C(void *, u8 *);
extern void fn_801FDEB4(void *, Vec3 *);
extern s32 fn_801FE05C(void *);

s32 fn_8007C354(void *arg)
{
    EffectState *state = fn_801FD6F4(arg);
    void *owner;
    void *model;
    void *transform;
    Vec3 localPosition;
    Vec3 *position;
    HitResult hit;
    u8 color[4];

    if (fn_8015E4E8(state) == 0) {
        if (fn_801FE52C(arg) != 0) {
            state->status = 2;
            return 0;
        }
        if (state != 0 && state->finished == 0) {
            owner = fn_80201814(state->owner);
            if (owner != 0) {
                if (fn_80155DB4() != 0) {
                    model = fn_80201C24(owner);
                    transform = fn_80201BC8(owner);
                    if (fn_8011F6A4(transform, 4, -1, -1, &hit, 1) != -1) {
                        localPosition = hit.normal;
                        position = &hit.position;
                        fn_801FE890(arg, &localPosition);
                    } else {
                        position = fn_8011F130(transform);
                    }
                    if (model != 0) {
                        switch (fn_80157AB8(model)) {
                        case 1:
                            color[0] = 255;
                            color[1] = 0;
                            color[2] = 0;
                            color[3] = 255;
                            fn_801FD80C(arg, color);
                            break;
                        case 2:
                            color[0] = 0;
                            color[1] = 0;
                            color[2] = 255;
                            color[3] = 255;
                            fn_801FD80C(arg, color);
                            break;
                        case 3:
                            color[0] = 0;
                            color[1] = 255;
                            color[2] = 0;
                            color[3] = 255;
                            fn_801FD80C(arg, color);
                            break;
                        case 4:
                            color[0] = 255;
                            color[1] = 0;
                            color[2] = 255;
                            color[3] = 255;
                            fn_801FD80C(arg, color);
                            break;
                        default:
                            fn_801FD80C(arg, lbl_8064B590);
                            break;
                        }
                    }
                    fn_801FDEB4(arg, position);
                    state->flags = 0x10000;
                    state->timer = 0;
                } else if (fn_801FE05C(arg) != 0) {
                    state->status = 2;
                }
            } else {
                state->finished = 1;
            }
        }
    }
    return 0;
}
