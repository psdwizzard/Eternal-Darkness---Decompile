typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TransformData {
    u32 words[13];
} TransformData;

typedef struct Vec2 {
    float x;
    float y;
    float z;
} Vec3;

extern void* lbl_8064C824;
extern void* lbl_8064C828;
extern void* lbl_8064C830;
extern u32 lbl_8064C820;
extern int lbl_8064C834;

extern void fn_801F683C(TransformData* value);
extern void* fn_80201B94();
extern void *fn_80201BC8();
extern int fn_80201B54();
extern int fn_80201B64(void* object);
extern void* fn_80201C48(void* object);
extern void fn_80201DD8(void* object, u32 value);
extern void fn_80211A6C();
extern unsigned long long fn_8020123C();

extern void fn_801A6E90(void);
extern void fn_801A6DEC(void* object);
extern void fn_801A6DF4(void* object);
extern void fn_801A6DFC(void* object, u32 value);
extern void fn_801A6E24(void* object, u32 value);
extern void fn_801A6E2C(void* object, u32 value);
extern void fn_801A5D28(void);
extern u32 fn_801A6D9C(void* object);
extern int fn_801A6D94(void* object);
extern void fn_801A665C(void* object, u32 value);
extern void fn_801A74A0(void* object, void* value);
extern void fn_801A74A8(void* object, void* value);
extern void fn_801A7864(void* object);
extern u32 fn_801A7840(void* object);
extern u32 fn_801A77D4(void* object);
extern void fn_801A7460(void* object, u32 value);
extern void fn_801A74D8(void* object, u32 value);
extern u32 fn_801A7780(void* object);
extern void fn_801A7560(void* object, u32 value);
extern void fn_801A75A0(void* object, u32 value);
extern void fn_801A74E8(void* object, u32 value);

extern float fn_8012B750(void* object);
extern u8 fn_80128EE4(void* object);
extern u32 fn_801290D0(void* object);
extern u32 fn_8011FB24(void* object);
extern u32 fn_8011FB3C(void* object);
extern int fn_80130718(void);
extern void fn_80144C4C(void* object);
extern u8 fn_8013017C(void* object);
extern void fn_80130434(void* object, u32 value);
extern int fn_801301B0(void* object, u32 first, u32 second);
extern void fn_800C2474(void* object, u32 value);

extern int fn_80048A60(void);
extern float fn_800490E8(float y, float x);
extern void fn_8004948C(void* view, void* object, u32 value);

void fn_80048C74(void* view)
{
    TransformData target;
    TransformData source;
    Vec3 direction;
    void* actor;
    u32 flags;
    void* object;
    void* callback;
    int special;
    u32 type;
    void* value;
    u32 state;

    fn_801F683C(&source);
    target = source;
    callback = fn_80201B94(view);
    actor = fn_80201BC8(view);
    object = (void*)fn_80201B54(view);
    fn_801A6E90();
    fn_80211A6C(&target.words[3], &target.words[0], &direction);
    fn_800490E8(direction.y, direction.x);

    fn_801A6DEC(lbl_8064C824);
    fn_8012B750(actor);
    fn_801A6DF4(lbl_8064C824);
    fn_801A6DFC(lbl_8064C824, fn_80128EE4(actor));
    fn_801A6E24(lbl_8064C824, fn_8011FB24(actor));
    fn_801A6E2C(lbl_8064C824, fn_8011FB3C(actor));
    fn_801A74A0(lbl_8064C828, object);
    value = fn_80201C48(callback);
    fn_801A74A8(lbl_8064C828, value);
    fn_801A7864(lbl_8064C828);

    if ((fn_801290D0(actor) & 4) != 0) {
        fn_801A6DFC(lbl_8064C824, 0);
    }
    fn_801A5D28();
    if (fn_80130718() != 0) {
        fn_80144C4C(lbl_8064C830);
    }

    flags = fn_801A6D9C(lbl_8064C824);
    if ((flags & 0x700) != 0) {
        if ((flags & 0x100) != 0) {
            fn_8020123C(0x29, object, object, lbl_8064C828);
        } else if ((flags & 0x200) != 0) {
            fn_8020123C(0x2A, object, object, lbl_8064C828);
        }
        if (fn_80048A60() == 0) {
            fn_801A75A0(lbl_8064C828, 0);
            fn_801A74E8(lbl_8064C828, 0x1000000);
        }
    }

    special = 0;
    if ((flags & 0x1000) != 0 && fn_801A7840(lbl_8064C828) == 8) {
        special = 1;
    }
    if ((flags & 2) != 0 || special != 0) {
        if (fn_801A6D94(lbl_8064C824) == 0) {
            fn_801A665C(lbl_8064C828, 1);
        }
        fn_8004948C(view, lbl_8064C828, 1);
        state = fn_801A77D4(lbl_8064C828);
        fn_801A7460(lbl_8064C828, state);
        if (fn_801A6D94(lbl_8064C824) == 0) {
            fn_801A74D8(lbl_8064C828, 4);
        }
        fn_801A7560(lbl_8064C828, fn_801A7780(lbl_8064C828));
        if (special != 0) {
            fn_801A74D8(lbl_8064C828, 0x40);
            fn_8020123C(0xF, object, object, lbl_8064C828);
        } else {
            fn_8020123C(0x28, object, object, lbl_8064C828);
        }
    }
    if ((flags & 4) != 0) {
        fn_8020123C(0xCF, object, object, lbl_8064C824);
    }
    if ((flags & 1) != 0) {
        fn_8020123C(0x2E, object, object, lbl_8064C824);
        flags = fn_801A6D9C(lbl_8064C824);
    }

    type = fn_80201B64(view);
    special = type == 0x27 || type == 0x28;
    if (fn_801A6D94(lbl_8064C824) == 0 && special == 0) {
        fn_80201DD8(callback, 0);
    }
    if (fn_801A6D94(lbl_8064C824) != 0) {
        lbl_8064C834 = 1;
        fn_8004948C(view, lbl_8064C828, 0);
        fn_801A7560(lbl_8064C828, fn_801A7780(lbl_8064C828));
        fn_8020123C(0x2B, object, object, lbl_8064C828);
        fn_8013017C(actor);
        if (fn_80130718() == 0) {
            fn_80130434(actor, 1);
            fn_801301B0(actor, 0, 0x10);
        }
    } else {
        if (lbl_8064C834 != 0) {
            fn_800C2474(actor, 1);
            lbl_8064C834 = 0;
        }
        lbl_8064C820 = 0;
        fn_801301B0(actor, 0x10, 0);
        if ((flags & 0x80) != 0) {
            fn_8020123C(0x2C, object, object, lbl_8064C824);
        } else {
            fn_8020123C(0x2D, object, object, lbl_8064C824);
        }
    }
}
