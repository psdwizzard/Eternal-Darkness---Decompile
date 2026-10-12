/* The C body matches retail. MWCC currently uses register-save helpers
 * in place of the retail stmw/lmw prologue and epilogue. */
typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct EffectState {
    u8 padding[0x15A];
    s16 countdown;
} EffectState;

typedef struct ObjectInfo {
    u8 padding[0x9F];
    u8 type;
} ObjectInfo;

extern void *fn_80200C38(void **);
extern int fn_80201B54(int *);
extern void *fn_80036D5C(void *);
extern void fn_80036DA4(void *, void *);
extern void *fn_80201B8C(u8 *);
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);
extern void fn_8012F58C(void *, u32, u32, u16, u16, u16);
extern void *fn_801A717C(void);
extern int fn_80201B44(void);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A7538(void *, u16);
extern void fn_801A7518(void *, s16);
extern u64 fn_8020123C(int, int, int, int);
extern void fn_801A7228(void *);
extern u32 lbl_8064E2C4;
extern u32 lbl_8064E2C8;
extern u32 lbl_8064E2CC;

void fn_8003DD4C(int *object, u8 *owner, EffectState *state, void **event)
{
    u32 start;
    u32 end;
    u32 color;
    ObjectInfo *info;
    void *payload;
    int objectId;
    int strength;
    void *effect;
    int source;
    int target;

    payload = fn_80200C38(event);
    objectId = fn_80201B54(object);
    if (!((u32)fn_80036D5C(object) & 0x20000)) {
        info = fn_80201B8C((u8 *)object);
        color = lbl_8064E2CC;
        end = lbl_8064E2C8;
        start = lbl_8064E2C4;
        fn_8012C62C(owner, 15, &start, (s8 *)&end, &color, 18);
        fn_8012F58C(owner, 15, 0, 1, 30, 8);
        state->countdown = 300;
        fn_80036DA4(object, (void *)((u32)fn_80036D5C(object) | 0x20000));
        strength = info->type == 10 ? 50 : 0;
        if (strength != 0) {
            effect = fn_801A717C();
            source = fn_80201B54(object);
            target = fn_80201B44();
            fn_801A74A0(effect, source);
            fn_801A74A8(effect, target);
            fn_801A7538(effect, 2);
            fn_801A7518(effect, strength);
            fn_8020123C(39, source, target, (int)effect);
            fn_801A7228(effect);
        }
    }
    if (payload != 0) {
        fn_8020123C(53, objectId, objectId, (int)payload);
    }
}
