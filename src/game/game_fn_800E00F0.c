typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Vec {
    float x;
    float y;
    float z;
} Vec;

extern void *fn_800DE3F8(void *);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern int fn_80200C20(void *);
extern void *fn_80201814(int);
extern void fn_8011F114(Vec *, void *);
extern unsigned long long fn_8020123C(int, int, void *, void *);
extern int fn_80036E50(void *);
extern void fn_8006749C(int);
extern void fn_80201BC8(void *);
extern int fn_80038464(void *, int, s16 *);
extern int fn_800389E0(void *, int, s16, int);
extern void fn_801AAE68(int, int, int, Vec *, int, int, int, u16, float, int);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_8012DBE8(void *, int, u8 *);
extern void fn_8012C62C(void *, int, int *, int *, int *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80120B4C(void *);
extern void fn_8016B400(int, int, int);
extern void *fn_801A717C(void);
extern void fn_801A74A0(void *, int);
extern void fn_801A74A8(void *, int);
extern void fn_801A7538(void *, int);
extern void fn_801A7518(void *, int);
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
    void *value;
    int id;
    Vec pos;
    u8 color[4];
    int a;
    int b;
    int c;
    s16 angle;

    value = fn_800DE3F8(object);
    id = fn_80201B44();
    owner = fn_80201B54(object);
    link = fn_80201814(fn_80200C20(message));
    fn_8011F114(&pos, actor);
    result = fn_8020123C(0x3B, id, value, 0) & 0xFFFFFFFFULL;
    if (link != 0 && fn_80036E50(link) == 6) {
        return;
    }
    if (result != 0) {
        void *other = fn_80201814((int)value);
        fn_8006749C(context->unk94);
        fn_80201BC8(other);
        fn_80038464(object, 0, &angle);
        fn_800389E0(object, 0, angle, 0);
        fn_801AAE68(0x20F, 100, 0, &pos, 2, 2, 0, lbl_8064D18C, lbl_8064F56C, 0);
        fn_801294DC(actor, 0x87, 0x20, 10);
        fn_8012DBE8(actor, 15, color);
        c = lbl_80651B08;
        b = lbl_8064F598;
        a = *(int *)color;
        fn_8012C62C(actor, 15, &a, &b, &c, 4);
        fn_80201D34(object, 0);
        fn_80201D1C(object, 1);
        fn_80120B4C(actor);
        fn_8016B400(0xAD2, owner, 0);
        fn_8020123C(0x7E, owner, target->unk54, 0);
    } else {
        void *work = fn_801A717C();
        fn_801A74A0(work, owner);
        fn_801A74A8(work, id);
        fn_801A7538(work, 2);
        fn_801A7518(work, -0x7D);
        fn_8020123C(0x27, owner, (void *)id, work);
        fn_801A7228(work);
        lbl_8064C578 = 4;
        fn_800CD094(object, message, 800);
        fn_801B1A1C(9, 60);
    }
}
