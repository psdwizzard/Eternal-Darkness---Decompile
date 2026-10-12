typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Context {
    /* 0x00 */ char unk0[0x8C];
    /* 0x8C */ void *state;
    /* 0x90 */ char unk90[0x9C - 0x90];
    /* 0x9C */ s16 timerOffset;
    /* 0x9E */ char unk9E;
    /* 0x9F */ u8 kind;
} Context;

typedef struct QueryResult {
    void *object;
} QueryResult;

extern s32 fn_80200C10(void *);
extern s32 fn_80200C20(void *);
extern s32 fn_80200C28(void *);
extern s32 fn_80200C38(void *);
extern void *fn_80201BC8(void *);
extern Context *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern s32 fn_80201B54(void *);
extern s32 fn_80201B44(void);
extern void *fn_80201B3C(void);
extern s32 fn_80201C48(void *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_8011F788(void *, f32);
extern void fn_8011F798(void *, f32);
extern void fn_8011F778(void *, f32);
extern void fn_800CA2C8(void *);
extern void fn_8012B324(void *);
extern void fn_8012B344(void *);
extern void fn_801E8328(int, void *);
extern void *fn_80049220(void *, int);
extern void *fn_80049304(void *, void *);
extern s32 fn_80093264(void);
extern u64 fn_8020123C();
extern void fn_801A7228(s32);
extern void fn_80068994(void *, void *);
extern void fn_8014D478(void *object, Vec3 *a, Vec3 *b, s32 c, s32 d,
                        void *data, s32 e);
extern s32 fn_801207F0(void *);
extern void fn_800CEA1C(s32 kind, s32 value, Vec3 *a, Vec3 *b, s32 c, s32 d,
                        void *data, float x, float y, float z);
extern void fn_801AAE68(float scale, s32 kind, s32 value, s32 a, void *object,
                        s32 b, s32 c, s32 d, unsigned short id, s32 extra);
extern void fn_800BD194(void *, void *);
extern void fn_800BD2DC(void *, void *);
extern void fn_800C9E50(void *);
extern QueryResult *fn_800BC100(int, Vec3 *, int *, int, int, int, int);
extern void fn_800BCCC4(void *, Vec3 *);
extern void fn_80201DD8(void *, int);
extern void fn_80201F44(void *, Vec3 *);
extern void fn_800BDEE4(void *, void *);
extern void fn_800BE010(void *, void *);
extern s32 fn_8011FAEC(void *);
extern s32 fn_8009A2B8(void *, void *, s32, void *, void *, int, int, int,
                       float);

extern s32 lbl_8064D5A8;
extern u32 lbl_8064D18C;
extern Vec3 lbl_802396A0;
extern char lbl_802FC5BC[];
extern const f32 lbl_8064ECB8;
extern const f32 lbl_8064ECBC;
extern const f32 lbl_8064ECC0;
extern const f32 lbl_8064ECC4;
extern const f32 lbl_8064ECC8;

s32 fn_80094F34(void *object, s32 state, void *event, u32 *out) {
    Vec3 pos;
    Vec3 target;
    Vec3 found_pos;
    Vec3 copy;
    int lookup;
    char *color;
    s32 kind;
    void *obj;
    Context *ctx;
    void *data;
    void *runtime;
    s32 id;
    s32 timer;

    kind = fn_80200C10(event);
    obj = fn_80201BC8(object);
    ctx = fn_80201B8C(object);
    data = ctx->state;
    runtime = fn_80201B94(object);
    id = fn_80201B54(object);
    fn_8011F114(&pos, obj);
    timer = lbl_8064D5A8 + ctx->timerOffset;

    if (state == 0) {
        if (kind == 1) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_8011F788(obj, lbl_8064ECB8);
            fn_8011F798(obj, lbl_8064ECB8);
            fn_8011F778(obj, lbl_8064ECB8);
            return 1;
        }
        if (kind == 0x39) {
            fn_800CA2C8(object);
            fn_8012B324(obj);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        }
        if (kind == 0x3B) {
            s32 result = 0;
            s32 sender = fn_80200C20(event);
            s32 self = fn_80201B44();
            s32 flag = fn_80200C38(event) & 1;
            if (sender == self && flag == 0) {
                void *entry = fn_80201B3C();
                void *link = fn_80049220(entry, 1);
                void *found = fn_80049304(entry, link);
                if (found != 0) {
                    Context *other = found != 0 ? fn_80201B8C(found) : 0;
                    if (other != 0 && other->kind == 0x12 &&
                        fn_80093264() == 0) {
                        result = 1;
                    }
                }
            }
            if (out != 0) {
                *out = result;
            }
            return 1;
        }
        if (kind == 0x65) {
            if (out != 0) {
                *out = 1;
            }
            return 1;
        }
        if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event),
                        fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event),
                        fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0xB) {
            fn_8020123C(8, id, id, 0);
            return 1;
        }
        if (kind == 0xE) {
            fn_80068994(object, event);
            return 1;
        }
        if (kind == 0x27) {
            fn_8020123C(8, id, id, 0);
            return 1;
        }
        if (kind == 8) {
            target = lbl_802396A0;
            fn_800CA2C8(object);
            color = lbl_802FC5BC + 0x18;
            fn_8014D478(obj, &pos, &target, 2, 2, color, 3);
            if (fn_801207F0(obj) != 0) {
                fn_800CEA1C(0x17, 3, &pos, &target, 2, 3, color,
                            lbl_8064ECBC, lbl_8064ECBC, lbl_8064ECC0);
            }
            fn_801AAE68(lbl_8064ECC4, 0x11, 0x64, 0, &pos, 2, 2, 0,
                        lbl_8064D18C, 0);
            fn_801E8328(2, object);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            return 1;
        }
        if (kind == 0x3E) {
            fn_800BD194(object, data);
            fn_800C9E50(object);
            return 1;
        }
        if (kind == 0x3D) {
            fn_800BD2DC(object, data);
            return 1;
        }
    } else if (state == 1) {
        if (kind == 3) {
            if ((timer & 0xFF) == 0) {
                QueryResult *found =
                    fn_800BC100(0, &pos, &lookup, 8, 0, 0, 0);
                if (found != 0) {
                    fn_800BCCC4(found->object, &found_pos);
                    fn_80201DD8(runtime, -1);
                    copy = found_pos;
                    fn_80201F44(object, &copy);
                    fn_800BDEE4(object, ctx->state);
                    fn_80201D2C(object, 0x3E);
                    fn_80201D14(object, 1);
                }
            }
            return 1;
        }
    } else if (state == 0x3E) {
        if (kind == 1) {
            return 1;
        }
        if (kind == 0x3D) {
            fn_800BD2DC(object, data);
            fn_8012B344(obj);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 3) {
            if ((timer & 0x1F) == 0) {
                fn_800BE010(object, data);
                if (fn_80201C48(runtime) != 0) {
                    fn_800BDEE4(object, data);
                }
                if (fn_8011FAEC(obj) & 0x10) {
                    fn_8012B344(obj);
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                } else if (fn_8009A2B8(object, obj, id, data, event, 3, 0x50,
                                       0, lbl_8064ECC8) != 0) {
                    fn_80201D2C(object, 1);
                    fn_80201D14(object, 1);
                }
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
