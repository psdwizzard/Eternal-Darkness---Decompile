typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
} Vec;

typedef struct ActorInfo {
    u8 pad0[0x19C];
    Vec position;
} ActorInfo;

typedef struct ObjectContext {
    u8 pad0[0x44];
    ActorInfo *actor;
} ObjectContext;

extern ObjectContext *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern void *fn_80201C48(void *);
extern void *fn_80201B54(void *);
extern void *fn_80201814(void *);
extern void *fn_80201BC8(void *);
extern void fn_8011F114(Vec *destination, Vec *source);
extern s32 fn_80074440(void *, void *, ActorInfo *, Vec *);
extern s32 fn_80074864(void *, s32, s32 *, u16 *, u8 *);
extern void *fn_801294DC(void *, s32, s32, s32);
extern u64 fn_8020123C(int kind, int arg1, int arg2, int arg3);
extern void *fn_801A717C(void);
extern f32 fn_8012B7D0(const void *a, const void *b);
extern f32 fn_8012B750(void *);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_80129BA4(void *, f32, f32);
extern void fn_801A74A0(void *, void *);
extern void fn_801A74A8(void *, void *);
extern void fn_801A74C8(void *, s32);
extern void fn_801A7560(void *, s32);
extern void fn_801A7538(void *, u16);
extern void fn_801A7518(void *, u8);
extern void fn_801A7550(void *, s32);
extern void fn_801A7558(void *, s32);
extern s32 fn_8011F130(void *);
extern void fn_801A764C(void *, s32);
extern void fn_801287C4(void *, void (*)(), void *, s32);
extern void fn_80128C28(void *, void (*)(), void *);
extern void fn_80128C44(void *, void (*)(), void *);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D14(void *, s32);
extern void fn_8012B344(void *);

extern void fn_80074040();
extern void fn_800740A0();
extern void fn_800740E8();
extern void fn_800741E8();
extern void fn_800746CC();
extern void fn_800747CC();
extern void fn_80204230();
extern void fn_802042A4();

extern Vec lbl_80239188;
extern f32 lbl_8064E870;
extern f32 lbl_8064E874;
extern f32 lbl_8064E878;

static inline f32 GetPositionAngle(const void *actor, Vec position)
{
    return fn_8012B7D0(actor, &position);
}

static inline Vec GetDefaultPosition(void)
{
    return lbl_80239188;
}

static inline s32 CanStartAnimation(void *object, void *actor, void *source,
                                    ActorInfo *info, Vec *offset, s32 *anim,
                                    u16 *flags, u8 *mode)
{
    s32 found = fn_80074440(actor, source, info, offset);
    s32 ok = 0;

    if (found != 0 && fn_80074864(object, 0, anim, flags, mode) != 0) {
        ok = 1;
    }
    return ok;
}

s32 fn_80073C64(void *object, void *actor)
{
    ObjectContext *context;
    void *target;
    void *owner;
    void *found;
    void *source;
    void *handle;
    void *event;
    s32 result;
    u32 eventStatus;
    f32 angle;
    f32 diff;
    Vec position;
    Vec offset;
    Vec sourcePosition;
    s32 anim;
    f32 delta;
    u16 flags;
    u8 mode;

    context = fn_80201B8C(object);
    target = fn_80201C48(fn_80201B94(object));
    owner = fn_80201B54(object);
    found = fn_80201814(target);
    source = found ? fn_80201BC8(found) : 0;
    position = source ? (fn_8011F114(&sourcePosition, source), sourcePosition)
                      : GetDefaultPosition();
    result = 0;
    if (found != 0 && source != 0) {
        if (CanStartAnimation(object, actor, source, context->actor, &offset,
                              &anim, &flags, &mode) != 0) {
            handle = fn_801294DC(actor, anim, 0x100, 6);
            if (handle != 0) {
                /* The low word of the event result reports whether it was accepted. */
                eventStatus = fn_8020123C(0x6B, (s32)owner, (s32)target, 0) & 0xFFFFFFFFULL;
                if (eventStatus != 0) {
                    event = fn_801A717C();
                    angle = GetPositionAngle(actor, position);
                    fn_8017A12C(&delta, fn_8012B750(actor), angle);
                    diff = delta;
                    if (diff < lbl_8064E870) {
                        diff = -diff;
                    }
                    if (diff > lbl_8064E874) {
                        fn_80129BA4(handle, angle, lbl_8064E878);
                    }
                    context->actor->position = position;
                    fn_801A74A0(event, owner);
                    fn_801A74A8(event, target);
                    fn_801A74C8(event, 1);
                    fn_801A7560(event, 0);
                    fn_801A7538(event, flags);
                    fn_801A7518(event, mode);
                    fn_801A7550(event, 0x6C);
                    fn_801A7558(event, 7);
                    fn_801A764C(event, fn_8011F130(actor));
                    fn_801287C4(handle, fn_800740E8, object, 0x18);
                    fn_801287C4(handle, fn_800741E8, event, 0x1A);
                    fn_801287C4(handle, fn_800740A0, object, 0x24);
                    fn_801287C4(handle, fn_800746CC, event, 0x20);
                    fn_801287C4(handle, fn_800747CC, event, 0x2B);
                    fn_801287C4(handle, fn_80074040, event, 0x32);
                    fn_801287C4(handle, fn_80074040, event, 0x3A);
                    fn_801287C4(handle, fn_80074040, event, 0x42);
                    fn_801287C4(handle, fn_80074040, event, 0x4A);
                    fn_801287C4(handle, fn_80074040, event, 0x52);
                    fn_801287C4(handle, fn_80074040, event, 0x5A);
                    fn_80128C28(handle, fn_80204230, event);
                    fn_80128C44(handle, fn_802042A4, event);
                    fn_80201D2C(object, 0x33);
                    fn_80201D14(object, 1);
                    result = 1;
                } else {
                    fn_8012B344(actor);
                }
            }
        }
    }
    return result;
}
