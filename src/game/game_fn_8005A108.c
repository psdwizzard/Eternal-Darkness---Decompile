typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct HandlerContext {
    void *value;
    u8 pad04[0x88];
    void *state;
} HandlerContext;

typedef struct HandlerState {
    u8 pad00[0x48];
    void *linked;
    u8 pad4C[0x102];
    s16 counter;
    u8 pad150[0x15];
    u8 progress;
} HandlerState;

typedef struct LinkedState {
    u8 pad00[0x64];
    void *linked;
} LinkedState;

#pragma use_lmw_stmw on

extern s32 lbl_8064C87C;
extern u32 lbl_8064D18C;
extern float lbl_8064E52C;
extern float lbl_8064E530;
extern float lbl_8064E534;
extern const float lbl_8064E538;
extern float lbl_8064E53C;
extern float lbl_8064E540;
extern float lbl_8064E544;
extern float lbl_8064E548;
extern Vec3 lbl_80243BD8;
extern char lbl_80243BE4[];
extern char lbl_802FC5BC[];

extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern u32 fn_80036D5C(void *context);
extern void fn_80036DA4(void *context, u32 flags);
extern void fn_80130434(void *object, s32 value);
extern void fn_801301B0(void *object, s32 a, s32 b);
extern void fn_8017A244(Vec3 *source, Vec4 *output, float scale);
extern void fn_8012CF08(void *object, s32 kind, Vec4 first, Vec4 second,
                        s32 a, s32 b, float scale);
extern void fn_8012F58C(void *object, s32 a, s32 b, s32 c, s32 d, s32 e);
extern int fn_80038308(void *, int, short *);
extern int fn_800389E0(void *context, s32 index, s16 value, s32 mode);
extern void *fn_8011F130(void *object);
extern void fn_801AAE68(float scale, s32 kind, s32 value, s32 a, void *object,
                        s32 b, s32 c, s32 d, unsigned short id, s32 extra);
extern void fn_8011E310(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern unsigned long long fn_8020123C();
extern void fn_800C2474(void *object, s32 value);
extern s32 fn_8006D3E4(u32 value, s32 mode);
extern int fn_80200C38();
extern s32 fn_80063D60(void *object, HandlerContext *handler, u8 value);
extern void fn_800C63D8(void);
extern u32 fn_8020216C(void *context);
extern void fn_8012B344(void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8012B690(void *object, char *name, Vec3 *output);
extern void PSVECNormalize(Vec3 *input, Vec3 *output);
extern void PSVECScale(Vec3 *input, Vec3 *output, float scale);
extern void fn_80205868(void *object, s32 value, Vec3 *position, s32 flags);
extern void fn_8014CBE8(void *context, s32 kind, s32 value, void *data);
extern s32 fn_8012FD1C(void *object, s32 index, Vec3 *output);
extern void fn_8014D478(void *object, Vec3 *a, Vec3 *b, s32 c, s32 d,
                        void *data, s32 e);
extern void fn_800CEA1C(s32 kind, s32 value, Vec3 *a, Vec3 *b, s32 c, s32 d,
                        void *data, float x, float y, float z);
extern int fn_80201B44();
extern u64 fn_802011D4(void *event);

s32 fn_8005A108(void *context, void *event, u32 *result)
{
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);
    s32 object_id = fn_80201B54(context);
    HandlerContext *handler = fn_80201B8C(context);
    HandlerState *state = (HandlerState *)handler->state;
    LinkedState *linked = (LinkedState *)handler->value;

    if (kind == 1) {
        Vec4 first, second;
        s16 value;
        u32 flags;
        lbl_8064C87C = 0;
        flags = fn_80036D5C(context);
        fn_80036DA4(context, flags | 0x40);
        state->counter = 0;
        fn_80130434(object, 0);
        fn_801301B0(object, 0, 0x20);
        fn_8017A244(&lbl_80243BD8, &first, lbl_8064E52C);
        fn_8017A244(&lbl_80243BD8, &second, lbl_8064E530);
        fn_8012CF08(object, 0, first, second, 1, 0, lbl_8064E534);
        fn_8012F58C(object, 0, 3, 0, 0, 0x20);
        fn_80038308(context, 1, &value);
        value = (value - 1) & -((value - 1) > 0);
        fn_800389E0(context, 1, value, 1);
        return 1;
    }
    if (kind == 3) {
        s16 value;
        lbl_8064C87C++;
        fn_80038308(context, 1, &value);
        if (lbl_8064C87C > 60) {
            lbl_8064C87C = 0;
            fn_801AAE68(lbl_8064E538, 606, 100, 0, fn_8011F130(object),
                        2, 2, 0, lbl_8064D18C, 0);
            value = (value - 1) & -((value - 1) > 0);
            fn_800389E0(context, 1, value, 1);
        }
        if ((fn_80036D5C(context) & 0x40) != 0)
            fn_8011E310(6, 20, 0, 0, 50, 1, 0);
        state->counter++;
        if (state->counter > 360) {
            fn_8020123C(152, object_id, (void *)object_id, 0);
            fn_8020123C(152, object_id, linked->linked, 0);
        }
        return 1;
    }
    if (kind == 2) {
        fn_800C2474(object, 0);
        fn_801301B0(object, 0x20, 0);
        return 1;
    }
    if (kind == 44) {
        u32 flags = fn_80036D5C(context);
        if ((flags & 0x40) != 0 && fn_8006D3E4(0x40000, 0) == 0) {
            void *value = (void *)fn_80200C38(event);
            if (value != 0) {
                state->progress += fn_80063D60(value, handler, state->progress);
                if (state->progress >= 12) {
                    fn_8020123C(152, object_id, linked->linked, 0);
                    fn_8020123C(152, object_id, (void *)object_id, 0);
                }
            }
        }
        return 1;
    }
    if (kind == 61) {
        fn_8020123C(152, object_id, state->linked, 0);
        fn_8020123C(152, object_id, (void *)object_id, 0);
        fn_800C63D8();
        return 1;
    }
    if (kind == 152) {
        u32 context_flags = fn_8020216C(context);
        Vec3 second;
        Vec3 position;
        u32 flags;
        fn_80036D5C(context);
        fn_8012B344(object);
        state->progress = 0;
        flags = fn_80036D5C(context);
        fn_80036DA4(context, flags & ~0x40);
        if ((context_flags & 0x800) != 0 || state->counter < 360) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
        } else {
            fn_8012B690(object, lbl_80243BE4, &position);
            PSVECNormalize(&position, &position);
            PSVECScale(&position, &position, lbl_8064E53C);
            fn_80205868(object, 0, &position, 0x2000);
            fn_8014CBE8(context, 20, 0, lbl_802FC5BC + 0x18);
            if (fn_8012FD1C(object, 1, &second) != 0) {
                fn_8014D478(object, &second, &position, 16, 4,
                            lbl_802FC5BC + 0x18, 3);
                fn_800CEA1C(23, 3, &second, &position, 2, 1,
                            lbl_802FC5BC + 0x18,
                            lbl_8064E540, lbl_8064E544, lbl_8064E548);
            }
            context = (void *)fn_80201B44();
            fn_8020123C(8, fn_80201B44(), context, 0);
        }
        return 1;
    }
    if (kind == 120) {
        fn_8020123C(152, object_id, linked->linked, 0);
        fn_8020123C(152, object_id, (void *)object_id, 0);
        if (result != 0)
            *result = fn_802011D4(event) & 0xFFFFFFFF;
        return 1;
    }
    if (kind == 32) {
        if (result != 0)
            *result = 0;
        return 1;
    }
    if (kind == 133) {
        fn_8020123C(152, object_id, linked->linked, 0);
        fn_8020123C(152, object_id, (void *)object_id, 0);
        if (result != 0)
            *result = fn_802011D4(event) & 0xFFFFFFFF;
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 53) return 1;
    if (kind == 40) return 1;
    if (kind == 135) return 1;
    if (kind == 175) return 1;
    if (kind == 147) return 1;
    return (u8)(kind == 31);
}
