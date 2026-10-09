typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct FrameEntry {
    s32 id;
    s32 pad[2];
} FrameEntry;

typedef struct AnimState {
    FrameEntry frames[8];   /* 0x00 */
    FrameEntry altFrames[8]; /* 0x60 */
    u8 padC0[0xE0 - 0xC0];
    s32 frame;              /* 0xE0 */
    u8 padE4[0xE8 - 0xE4];
    s32 unkE8;              /* 0xE8 */
    u8 padEC[0xFC - 0xEC];
    u32 unkFC;              /* 0xFC */
    u16 flags;              /* 0x100 */
} AnimState;

typedef struct Actor {
    u8 pad[0x94];
    s32 unk94;
} Actor;

extern void fn_8011F114(Vec3 *);
extern int fn_80201B54(void *);
extern void *fn_80201B94(void *);
extern void *fn_80201C48(void *);
extern void *fn_80201814(void *);
extern void *fn_80201B8C(void *);
extern int fn_80038308(void *, int, short *);
extern int fn_80038464(void *, int, short *);
extern void fn_802045AC(void *, Vec3 *);
extern int fn_80179064(int, int, int, int);
extern int fn_8009C048(void *, AnimState *);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern float fn_8012B7D0(void *, Vec3);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern int fn_8012AFC4(void *);
extern void fn_80129A00(void *, s32, s32, f32, f32);
extern void fn_8012998C(void *, f32);

extern f32 lbl_8064ED4C;
extern f32 lbl_8064ED6C;
extern f32 lbl_8064ED70;
extern f32 lbl_8064ED74;
extern f32 lbl_8064ED78;
extern f32 lbl_8064ED7C;

int fn_8009BD50(void *obj, void *cam, AnimState *state) {
    Vec3 camPos;
    Vec3 objPos;
    f32 angle;
    f32 dist;
    short cur;
    short max;
    void *active;
    Actor *actor;
    f32 ratio;
    FrameEntry *frames;
    s32 sfx;
    f32 vol;

    fn_8011F114(&camPos);
    fn_80201B54(obj);
    active = fn_80201814(fn_80201C48(fn_80201B94(obj)));
    actor = fn_80201B8C(obj);
    fn_80038308(obj, 0, &cur);
    fn_80038464(obj, 0, &max);
    ratio = (f32)cur / (f32)max;
    if (ratio < lbl_8064ED6C) {
        if (!(state->flags & 2)) {
            state->flags |= 2;
            state->frame = 0;
        }
    } else if (ratio > lbl_8064ED70) {
        if (state->flags & 2) {
            state->flags &= ~2;
            state->frame = 0;
        }
    }
    fn_802045AC(obj, &objPos);
    fn_80179064((int)camPos.x, (int)camPos.y, (int)objPos.x, (int)objPos.y);

    if (active != 0 && state->unkE8 <= 0 && state->unkFC == 0) {
        if (fn_8009C048(obj, state)) {
            fn_801294DC(cam, 0x4E, 0x20, 6);
            fn_80201D2C(obj, 0x40);
            fn_80201D14(obj, 1);
        }
        state->frame++;
        if (state->frame >= 8) {
            state->frame = 0;
        }
        frames = state->frames;
        if (state->flags & 2) {
            frames = state->altFrames;
        }
        if (frames[state->frame].id == 0) {
            state->frame = 0;
        }
    } else {
        dist = fn_8012B7D0(cam, objPos);
        fn_8017A12C(&angle, fn_8012B750(cam), dist);
        ratio = angle;
        if (ratio < lbl_8064ED4C) {
            ratio = -ratio;
        }
        if (ratio > lbl_8064ED74 && !fn_8012AFC4(cam)) {
            sfx = 0x88;
            if (angle < lbl_8064ED4C) {
                sfx = 0x89;
            }
            vol = lbl_8064ED78;
            if (actor->unk94 == 1) {
                vol = lbl_8064ED7C;
            }
            fn_80129A00(cam, sfx, 5, dist, vol);
        } else if (fn_8012AFC4(cam)) {
            fn_8012998C(cam, dist);
        }
        return 1;
    }
    return 0;
}
