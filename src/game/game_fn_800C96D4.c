typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

#define NULL ((void *)0)

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern u8 fn_800CC2D8(void *, int);
extern void fn_80120AD0(void *, const void *, u16, u16, float, float);
extern int fn_801261F4(void *);
extern void fn_8012C478(void *, int, int);
extern void *fn_8012C62C(void *, int, void *, void *, void *, int);
extern int fn_80157E1C(void *);
extern void *fn_80157E24(void *, int);
extern void *fn_80158598(int, int);
extern void fn_801D13D8(int, int);
extern int fn_801DAC18(int, int);
extern int fn_801E2004(int);
extern void *fn_80201814();
extern int fn_80201AE4(void);
extern int fn_80201B54(void *);
extern void *fn_80201B8C();
extern void *fn_80201B9C(void);
extern void *fn_80201BC8(void *);
extern void *fn_80204844(void *, int);

extern float lbl_8064F29C;
extern Color lbl_80651A78;
extern Color lbl_80651A7C;
extern Color lbl_80651A80;

typedef struct UnkInner {
    u8 pad[0x18];
    int unk18;
} UnkInner;

typedef struct UnkData {
    u8 pad[0x3C];
    UnkInner *unk3C;
} UnkData;

static inline void setColors(void *model, Color a, Color b, Color c) {
    fn_8012C62C(model, 0xF, &a, &b, &c, 4);
}

void fn_800C96D4(void *object, u8 alpha0, s8 alpha2, u8 alpha1, u16 arg4, int arg5, float scale) {
    Color c0;
    Color c1;
    Color c2;
    int id;
    int enabled;
    int result;
    int count;
    void *model;
    int flags;
    void *list;
    int i;
    void *member;

    c0 = lbl_80651A78;
    c1 = lbl_80651A7C;
    c2 = lbl_80651A80;
    model = fn_80201BC8(object);
    id = fn_80201B54(object);
    fn_801261F4(model);
    c0.a = alpha0;
    enabled = alpha2 > 0;
    c2.a = alpha2;
    c1.a = alpha1;
    flags = enabled ? 0x800 : 0x1000;
    flags |= 6;
    fn_80120AD0(model, 0, arg4, flags, lbl_8064F29C, scale);
    if (fn_801E2004(id) != 4) {
        setColors(model, c0, c2, c1);
    }

    list = fn_80158598(id, 0);
    if (list != NULL) {
        count = fn_80157E1C(list);
        for (i = 0; i < count; i++) {
            member = fn_80201814(fn_80157E24(list, i));
            if (member == NULL) {
                continue;
            }
            member = fn_80201BC8(member);
            if (member == NULL) {
                continue;
            }
            fn_80120AD0(member, 0, arg4, flags, lbl_8064F29C, scale);
            if (fn_801E2004(id) == 4) {
                continue;
            }
            fn_801261F4(member);
            fn_8012C478(member, 0xF, 1);
            if (fn_800CC2D8(member, 0)) {
                fn_8012C478(member, 0x10, 0);
            }
            if (fn_800CC2D8(member, 1)) {
                fn_8012C478(member, 0x11, 0);
            }
            setColors(member, c0, c2, c1);
        }
    }

    if (id == fn_80201AE4()) {
        int ref;
        if (fn_80204844(fn_80201B9C(), 0x22) != NULL &&
            (ref = ((UnkData *)fn_80201B8C())->unk3C->unk18) != 0) {
            member = fn_80201814(ref);
            if (member != NULL) {
                member = fn_80201BC8(member);
                fn_801261F4(member);
                setColors(member, c0, c2, c1);
                result = 1;
            }
        }
    }
    if (fn_801DAC18(id, enabled)) {
        result = 1;
    }
    if (enabled && result) {
        fn_801D13D8(id, arg5);
    }
}
