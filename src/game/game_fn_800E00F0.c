typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Entry80201814 Entry80201814;
typedef struct Object80201D34 Object80201D34;
typedef struct Object80201D1C Object80201D1C;

extern int fn_800DE3F8(void);
extern int fn_80201B44(void);
extern int fn_80201B54(int *);
extern int fn_80200C20(int *);
extern Entry80201814 *fn_80201814(int);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern int fn_80036E50(void *);
extern int fn_8006749C(int);
extern void *fn_80201BC8(void *);
extern int fn_80038464(void *, int, s16 *);
extern int fn_800389E0(void *, int, s16, int);
extern int fn_801AAE68(u16, u8, u8, float, Vec3 *, s8, u8, u8, u16, u32);
extern u8 *fn_801294DC(void *, int, int, int);
extern u16 fn_8012DBE8(u8 *, u32, u8 *);
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);
extern void fn_80201D34(Object80201D34 *, int);
extern void fn_80201D1C(Object80201D1C *, u8);
extern void fn_80120B4C(void *);
extern void fn_8016B400(int, void *, void *);
extern void *fn_801A717C(void);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A7538(void *, u16);
extern void fn_801A7518(void *, s16);
extern void fn_801A7228(void *);
extern void fn_800CD094(void *, void *, int);
extern void fn_801B1A1C(int, int);

extern int lbl_8064C578;
extern int lbl_8064D18C;
extern const float lbl_8064F56C;
extern const int lbl_8064F598;
extern int lbl_80651B08;

typedef struct Context {
    u8 pad0[0x94];
    int unk94;
} Context;

typedef struct Target {
    u8 pad0[0x54];
    void *unk54;
} Target;

void fn_800E00F0(void *object, void *actor, Context *context, Target *target, void *message)
{
    void *link;
    int result;
    int owner;
    int value;
    int id;
    Vec3 pos;
    u8 color[4];
    int a;
    int b;
    int c;
    s16 angle;

    value = fn_800DE3F8();
    id = fn_80201B44();
    owner = fn_80201B54(object);
    link = fn_80201814(fn_80200C20(message));
    fn_8011F114(&pos, actor);
    result = fn_8020123C(0x3B, id, value, 0) & 0xFFFFFFFFULL;
    if (link != 0 && fn_80036E50(link) == 6) {
        return;
    }
    if (result != 0) {
        void *other = fn_80201814(value);
        fn_8006749C(context->unk94);
        fn_80201BC8(other);
        fn_80038464(object, 0, &angle);
        fn_800389E0(object, 0, angle, 0);
        fn_801AAE68(0x20F, 100, 0, lbl_8064F56C, &pos, 2, 2, 0, lbl_8064D18C, 0);
        fn_801294DC(actor, 0x87, 0x20, 10);
        fn_8012DBE8(actor, 15, color);
        c = lbl_80651B08;
        b = lbl_8064F598;
        a = *(int *)color;
        fn_8012C62C(actor, 15, &a, (s8 *)&b, &c, 4);
        fn_80201D34(object, 0);
        fn_80201D1C(object, 1);
        fn_80120B4C(actor);
        fn_8016B400(0xAD2, (void *)owner, 0);
        fn_8020123C(0x7E, owner, (int)target->unk54, 0);
    } else {
        void *work = fn_801A717C();
        fn_801A74A0(work, owner);
        fn_801A74A8(work, id);
        fn_801A7538(work, 2);
        fn_801A7518(work, -0x7D);
        fn_8020123C(0x27, owner, id, (int)work);
        fn_801A7228(work);
        lbl_8064C578 = 4;
        fn_800CD094(object, message, 800);
        fn_801B1A1C(9, 60);
    }
}
