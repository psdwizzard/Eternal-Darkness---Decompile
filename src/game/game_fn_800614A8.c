typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define NULL ((void *)0)

#pragma use_lmw_stmw on

extern M2C_UNK fn_800359A0(s32, u32);                      /* extern */
extern s32 fn_80035FB8(s32, void *, M2C_UNK *, void *, M2C_UNK *, void *); /* extern */
extern s32 fn_80036D5C(s32);                               /* extern */
extern void fn_80036DA4(s32, s32);                         /* extern */
extern s32 fn_80036E50(void *);                                  /* extern */
extern int fn_80038308(void *, int, short *);           /* extern */
extern M2C_UNK fn_800389E0(s32, M2C_UNK, s16, M2C_UNK);    /* extern */
extern s32 fn_8003C04C(s32);                               /* extern */
extern M2C_UNK fn_8003C114(s32, u32, s32);                 /* extern */
extern M2C_UNK fn_8003E5DC(s32, u32, s32, void *);         /* extern */
extern s32 fn_800460EC();                                  /* extern */
extern s32 fn_8005E9E4(s32, s32);                          /* extern */
extern M2C_UNK fn_8005EA38(s32, s32, s32, f32 *);          /* extern */
extern M2C_UNK fn_8005EC6C(s32, s32, u32, void *, s32);    /* extern */
extern M2C_UNK fn_8005FD84(s32, s32, u32, void *, void *); /* extern */
extern M2C_UNK fn_80060C24(u32, s32, s8);                  /* extern */
extern s32 fn_80060D4C(s32, u32, s32, s32, s8);            /* extern */
extern s32 fn_80060F10(s32, u32, s32);                     /* extern */
extern M2C_UNK fn_80060F9C(s32, u32, s32, void *, s32, s32, s8); /* extern */
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_8011F114();                        /* extern */
extern s32 fn_8011F598(u32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
extern M2C_UNK fn_8011F778(u32, f32);                      /* extern */
extern M2C_UNK fn_8011F788(u32, f32);                      /* extern */
extern M2C_UNK fn_8011F798(u32, f32);                      /* extern */
extern unsigned int fn_8011FA8C(u32, M2C_UNK, M2C_UNK);            /* extern */
extern s32 fn_8011FF38();                                  /* extern */
extern M2C_UNK fn_80120AD0(u32, M2C_UNK, M2C_UNK, M2C_UNK, f32, f32); /* extern */
extern M2C_UNK fn_801261F4(u32);                           /* extern */
#define FN_80128E30_RETURN u32
#define FN_80128E30_PARAMETERS u32
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);                               /* extern */
extern s32 fn_80128EAC(u32);                               /* extern */
extern M2C_UNK fn_80128F74(u32, s32);                      /* extern */
extern s32 fn_801290D0(u32);                               /* extern */
extern void *fn_801294DC(void *, int, int, int);   /* extern */
#define fn_801294DC(a, b, c, d) fn_801294DC((void *)(a), (b), (c), (d))
extern M2C_UNK fn_801296F8(u32, M2C_UNK);                  /* extern */
extern M2C_UNK fn_8012B324(u32);                           /* extern */
extern void fn_8012B344(void*);                              /* extern */
extern void* fn_8012C62C(u32, M2C_UNK, s32 *, s32 *, s32 *, M2C_UNK); /* extern */
extern M2C_UNK fn_8012FE10(u32, M2C_UNK, f32 *);           /* extern */
extern s32 fn_8012FF34(u32, f32 *, M2C_UNK, M2C_UNK);      /* extern */
extern s32 fn_8013017C(u32);                               /* extern */
extern void fn_801301B0(u32, M2C_UNK, M2C_UNK);            /* extern */
extern M2C_UNK fn_801302BC(u32, M2C_UNK);                  /* extern */
extern s32 fn_801305D4(u32);                               /* extern */
extern M2C_UNK fn_80179064(s32, s32, s32, s32);            /* extern */
extern s32 fn_801A717C();                                  /* extern */
extern void fn_801A7228();                                 /* extern */
extern M2C_UNK fn_801A7470();                              /* extern */
extern s32 fn_801A7488();                                  /* extern */
extern void fn_801A74A0(s32, s32);                         /* extern */
extern void fn_801A74A8(s32, s32);                         /* extern */
extern s32 fn_801A74C0();                                  /* extern */
extern void fn_801A764C(s32, f32 *);                       /* extern */
extern M2C_UNK fn_801A977C(u32, M2C_UNK);                  /* extern */
extern M2C_UNK fn_801AAE68(M2C_UNK, M2C_UNK, M2C_UNK, f32, f32 *, M2C_UNK, M2C_UNK, M2C_UNK, u16, u32); /* extern */
extern M2C_UNK fn_801D14CC(s32);                           /* extern */
extern int fn_801E8328();                      /* extern */
extern s32 fn_802006D4(s32, s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern int fn_80200C10(void *);                           /* extern */
extern s32 fn_80200C20(s32);                               /* extern */
extern s32 fn_80200C28(s32);                               /* extern */
extern int fn_80200C38();                               /* extern */
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a, b, c, d, e) fn_8020104C((a), (void *)(b), (void *)(c), (int)(d), (e))
extern unsigned long long fn_8020123C();                   /* extern */
extern M2C_UNK fn_80201350(s32, M2C_UNK);                  /* extern */
extern void *fn_80201814(s32);                                /* extern */
extern int fn_80201B54();                                 /* extern */
extern void *fn_80201B8C();                               /* extern */
extern void* fn_80201B94();                               /* extern */
extern void *fn_80201B9C();                           /* extern */
extern void *fn_80201BC8();                               /* extern */
extern s32 fn_80201C48(s32);                               /* extern */
extern void fn_80201D14(void *, int);           /* extern */
extern void fn_80201D1C(void *, s32);                     /* extern */
extern void fn_80201D2C(void *, int);           /* extern */
extern void fn_80201D34(void *, s32);                     /* extern */
extern int fn_80201EB8();                  /* extern */
extern u8 fn_80204434(u32, f32 *, M2C_UNK, f32); /* extern */
extern M2C_UNK fn_802045AC(s32, f32 *);                    /* extern */
extern void *fn_80204844(void *, s32);                       /* extern */
extern M2C_UNK fn_80204FDC(s32);                           /* extern */
extern M2C_UNK fn_80064B38(s32, s32, s32 *); /* extern */
extern s32 fn_800654F8(); /* extern */
extern M2C_UNK fn_80066754(s32, s32, s32 *); /* extern */
extern M2C_UNK fn_80066888(u32, s32, f32, f32); /* extern */
extern M2C_UNK fn_80066A0C(s32, s32); /* extern */
extern s32 fn_80066D04(s32, M2C_UNK); /* extern */
extern M2C_UNK fn_80067180(s32); /* extern */
extern M2C_UNK fn_800674E4(s32, s32); /* extern */
extern M2C_UNK fn_80067650(s32, s32); /* extern */
extern M2C_UNK fn_80068994(s32, s32); /* extern */
extern s32 fn_8006D344(void *, M2C_UNK, M2C_UNK); /* extern */
extern void *fn_8006D444(void *); /* extern */
extern M2C_UNK fn_800BD194(s32, void *); /* extern */
extern M2C_UNK fn_800BD2DC(s32, void *); /* extern */
extern M2C_UNK fn_800BDEE4(s32, void *); /* extern */
extern M2C_UNK fn_800BE010(s32, void *); /* extern */
extern s32 fn_800BE86C(u32, void *, M2C_UNK, M2C_UNK, f32); /* extern */
extern M2C_UNK fn_800BE8D4(s32); /* extern */
extern M2C_UNK fn_800C9AD4(s32, u32); /* extern */
extern M2C_UNK fn_800C9B08(s32, u32, s32); /* extern */
extern M2C_UNK fn_800C9B74(s32, u32); /* extern */
extern s32 fn_800C9BA8(u32, void *); /* extern */
extern M2C_UNK fn_800C9C60(s32); /* extern */
extern M2C_UNK fn_800C9D68(s32); /* extern */
extern M2C_UNK fn_800C9E50(s32); /* extern */
extern s32 fn_800CA13C(u8); /* extern */
extern M2C_UNK fn_800CA1BC(s32, u32, s32, s32 *); /* extern */
extern M2C_UNK fn_800CA2C8(s32); /* extern */
extern s32 fn_800CAF7C(s32); /* extern */
extern M2C_UNK fn_800CC4DC(s32); /* extern */
extern M2C_UNK fn_800CC860(s32, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK fn_800CD094(s32, s32, M2C_UNK); /* extern */
extern M2C_UNK fn_800CF598(s32); /* extern */
extern M2C_UNK fn_800E0708(s32, s32, M2C_UNK); /* extern */
extern M2C_UNK fn_800EA0FC(s32, void *, s32, s32, s32 *); /* extern */
extern M2C_UNK fn_800EA3A0(s32, void *); /* extern */
extern s8 lbl_80243C30[];
extern M2C_UNK lbl_8064B508;
extern M2C_UNK lbl_8064B510;
extern M2C_UNK lbl_8064B518;
extern M2C_UNK lbl_8064B51C;
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
extern f32 lbl_8064E5BC;
extern f32 lbl_8064E5DC;
extern f32 lbl_8064E608;
extern s32 lbl_8064E60C;
extern s32 lbl_8064E610;
extern f32 lbl_8064E614;
extern f32 lbl_8064E618;
extern f32 lbl_8064E61C;
extern f32 lbl_8064E620;
extern f32 lbl_8064E624;
extern f32 lbl_8064E628;
extern f32 lbl_8064E62C;
extern f32 lbl_8064E630;
extern f32 lbl_8064E634;
extern s32 lbl_80651954;

typedef struct Fn800614A8Vec {
    f32 x;
    f32 y;
    f32 z;
} Fn800614A8Vec;

/* Both position-producing callees write all three float components. */
typedef struct Fn800614A8Pair {
    f32 x;
    f32 y;
    f32 z;
} Fn800614A8Pair;

typedef struct Fn800614A8Arg {
    s32 initial;
    s32 value;
} Fn800614A8Arg;

#define sp80 vec80.x
#define sp84 vec80.y
#define sp88 vec80.z
#define sp74 vec74.x
#define sp78 vec74.y
#define sp7C vec74.z
#define sp68 vec68.x
#define sp6C vec68.y
#define sp70 vec68.z
#define sp50 vec50.x
#define sp54 vec50.y
#define sp58 vec50.z
#define sp44 vec44.x
#define sp48 vec44.y
#define sp4C vec44.z
#define sp38 vec38.x
#define sp3C vec38.y
#define sp40 vec38.z
#define sp2C vec2C.x
#define sp30 vec2C.y
#define sp34 vec2C.z
#define sp8C pair8C.x
#define sp90 pair8C.y
#define sp5C pair5C.x
#define sp60 pair5C.y
#define sp14 arg14.initial
#define sp18 arg14.value
#define sp1C arg1C.initial
#define sp20 arg1C.value
#define sp24 arg24.initial
#define sp28 arg24.value

/* Dispatch order follows the retail comparison chains. */
s32 fn_800614A8(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s8 *eventData = lbl_80243C30;
    /* fn_8011F598 writes the result through offset 0x20. */
    struct { s32 second; s32 first; u8 data[0x18]; f32 value; } searchResult;
    Fn800614A8Pair pair8C;
    Fn800614A8Vec vec80;
    Fn800614A8Vec vec74;
    Fn800614A8Vec vec68;
    Fn800614A8Pair pair5C;
    Fn800614A8Vec vec50;
    Fn800614A8Vec vec44;
    Fn800614A8Vec vec38;
    Fn800614A8Vec vec2C;
    Fn800614A8Arg arg24;
    Fn800614A8Arg arg1C;
    Fn800614A8Arg arg14;
    s16 sp10;
    f32 temp_f2;
    s16 temp_r3;
    s32 temp_r3_10;
    s32 temp_r3_11;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s16 temp_r6;
    s16 temp_r6_2;
    s32 var_r0;
    s16 var_r3;
    s16 var_r3_2;
    s16 var_r3_3;
    s32 temp_r15;
    s32 temp_r15_2;
    s32 temp_r15_3;
    s32 temp_r15_4;
    s32 temp_r15_5;
    s32 temp_r15_6;
    s32 temp_r15_7;
    s32 temp_r15_8;
    s32 temp_r15_9;
    s32 temp_r16;
    s32 temp_r16_2;
    s32 temp_r16_3;
    s32 temp_r16_4;
    s32 temp_r16_5;
    s32 temp_r17;
    s32 temp_r18;
    s32 temp_r20;
    s32 temp_r23;
    s32 temp_r26;
    s32 temp_r3_12;
    s32 temp_r3_13;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r5_2;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r0_9;
    s32 var_r15;
    s32 var_r15_4;
    s32 var_r15_5;
    s32 var_r16;
    s32 var_r3_4;
    s8 temp_r19;
    u32 temp_r31;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 temp_r5;
    u32 var_r15_2;
    u32 var_r15_3;
    void *temp_r21;
    void *temp_r27;
    void *temp_r28;
    void *temp_r4;
    void *eventObject;

    temp_r23 = fn_80200C10((void *)arg2);
    temp_r31 = (u32)fn_80201BC8(arg0);
    temp_r21 = fn_80201B8C(arg0);
    temp_r27 = M2C_FIELD(temp_r21, void **, 0x8C);
    temp_r28 = M2C_FIELD(temp_r21, void **, 8);
    temp_r17 = (s32)fn_80201B94(arg0);
    temp_r26 = fn_80201B54(arg0);
    fn_8011F114(&sp8C, (void *)temp_r31);
    temp_r4 = M2C_FIELD(temp_r21, void **, 0x8C);
    temp_r20 = lbl_8064D5A8 + M2C_FIELD(temp_r21, s16 *, 0x9C);
    temp_r19 = (s8) M2C_FIELD(temp_r4, u8 *, 0x161);
    temp_r18 = fn_80201EB8((void *)arg0);
    if (temp_r23 == 3) {
        var_r16 = 0;
        if ((fn_80066D04(arg0, 3) == 0) && (fn_80066D04(arg0, 2) == 0)) {
            var_r16 = 1;
        }
        temp_r15 = fn_8005E9E4(arg0, temp_r17);
        fn_800CC4DC(arg0);
        var_r3 = M2C_FIELD(temp_r27, s16 *, 0x150);
        if (var_r3 >= 1) {
            var_r3 -= 1;
        }
        M2C_FIELD(temp_r27, s16 *, 0x150) = var_r3;
        var_r3_2 = M2C_FIELD(temp_r27, s16 *, 0x158);
        if (var_r3_2 >= 1) {
            var_r3_2 -= 1;
        }
        M2C_FIELD(temp_r27, s16 *, 0x158) = var_r3_2;
        if ((temp_r15 > 0x3E8) || (M2C_FIELD(M2C_FIELD(temp_r21, void **, 0x8C), s32 *, 0) & 0x800000) || (var_r16 != 0)) {
            var_r3_3 = M2C_FIELD(temp_r27, s16 *, 0x14E);
            if (var_r3_3 >= 1) {
                var_r3_3 -= 1;
            }
            M2C_FIELD(temp_r27, s16 *, 0x14E) = var_r3_3;
        }
        temp_r3 = M2C_FIELD(temp_r28, s16 *, 0x86);
        if (temp_r3 <= 1) {
            var_r0 = 0;
        } else {
            var_r0 = temp_r3 - 1;
        }
        M2C_FIELD(temp_r28, s16 *, 0x86) = var_r0;
        fn_800C9C60(arg0);
        if ((u8) lbl_8064D5A8 == 0) {
            fn_800C9D68(arg0);
        }
        if ((fn_8013017C(temp_r31) & 0x40) && (fn_801305D4(temp_r31) == 0)) {
            fn_801301B0(temp_r31, 0x40, 0);
        }
    }
    do {
        if (arg1 == 0x0) {
            do {
                if (temp_r23 == 0x1) {
                    M2C_FIELD(temp_r28, s32 *, 0x78) = rand() % 8;
                    M2C_FIELD(temp_r28, s16 *, 0x86) = 0x1E;
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0xF1) {
                    fn_8005EC6C(temp_r18, arg0, temp_r31, temp_r21, arg2);
                    return 1;
                } else if (temp_r23 == 0xF5) {
                    fn_8005EC6C(temp_r18, arg0, temp_r31, temp_r21, arg2);
                    return 1;
                } else if (temp_r23 == 0xDF) {
                    fn_8005EA38(temp_r18, arg0, arg2, &sp8C);
                    return 1;
                } else if (temp_r23 == 0x8) {
                    if (temp_r18 != (s32) lbl_8064D18C) {
                        fn_801E8328(2, arg0);
                    } else {
                        fn_800CD094(arg0, arg2, 0x3C0);
                    }
                    return 1;
                } else if (temp_r23 == 0x3D) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_800BD2DC(arg0, temp_r27);
                    return 1;
                } else if (temp_r23 == 0x3E) {
                    temp_r3_4 = fn_80036D5C(arg0);
                    if (temp_r3_4 & 0x08000000) {
                        fn_80036DA4(arg0, temp_r3_4 & 0xF7FFFFFF);
                        fn_801261F4(temp_r31);
                        sp14 = lbl_8064E610;
                        sp18 = lbl_8064E610;
                        sp1C = lbl_80651954;
                        sp20 = lbl_80651954;
                        sp24 = lbl_8064E60C;
                        sp28 = lbl_8064E60C;
                        fn_8012C62C(temp_r31, 0xF, &sp28, &sp20, &sp18, 4);
                        fn_8011FA8C(temp_r31, 0, 0x100);
                    }
                    fn_800BD194(arg0, temp_r27);
                    fn_800C9E50(arg0);
                    M2C_FIELD(temp_r28, s8 *, 0x88) = 0;
                    fn_801D14CC(temp_r26);
                    return 1;
                } else if (temp_r23 == 0xC9) {
                    if (fn_8011FF38() != 0) {
                        fn_8011FA8C(temp_r31, 0, 0x20000000);
                        fn_801AAE68(0x1F1, 0x64, 0, lbl_8064E5BC, &sp8C, 2, 2, 0, (u16) lbl_8064D18C, 0);
                    }
                    return 1;
                } else if (temp_r23 == 0x67) {
                    fn_800C9B08(arg0, temp_r31, arg2);
                    return 1;
                } else if (temp_r23 == 0xED) {
                    temp_r16 = fn_80200C38(arg2);
                    temp_r15_2 = fn_80200C28(arg2);
                    fn_8020123C(0xB, fn_80200C20(arg2), temp_r15_2, temp_r16);
                    fn_801A7228(fn_80200C38(arg2));
                    return 1;
                } else if (temp_r23 == 0x3A) {
                    temp_r16_2 = fn_80200C38(arg2);
                    temp_r15_3 = fn_80200C28(arg2);
                    fn_8020123C(0x27, fn_80200C20(arg2), temp_r15_3, temp_r16_2);
                    fn_801A7228(fn_80200C38(arg2));
                    return 1;
                } else if (temp_r23 == 0xB) {
                    if (fn_8006D344(fn_8006D444(fn_80204844(fn_80201B9C(), 0x20)), 0x80000, 0) != 0) {
                        fn_80067180(arg0);
                        var_r3_4 = 1;
                    } else {
                        var_r3_4 = fn_800654F8(fn_80200C38(arg2));
                    }
                    if (arg3 != NULL) {
                        *arg3 = var_r3_4;
                    }
                    return 1;
                } else if (temp_r23 == 0x65) {
                    fn_800359A0(arg0, (u32)fn_80201814(fn_80200C20(arg2)));
                    if (arg3 != NULL) {
                        *arg3 = 1;
                    }
                    return 1;
                } else if (temp_r23 == 0x39) {
                    fn_800CA2C8(arg0);
                    fn_800EA3A0(arg0, temp_r27);
                    fn_8012B324(temp_r31);
                    fn_8011FA8C(temp_r31, 0xC0, 0);
                    fn_80201D34((void *)arg0, 0);
                    fn_80201D1C((void *)arg0, 1);
                    fn_801E8328(2, arg0);
                    return 1;
                } else if (temp_r23 == 0xE) {
                    fn_80068994(arg0, arg2);
                    return 1;
                } else if (temp_r23 == 0x27) {
                    fn_80064B38(arg0, arg2, arg3);
                    return 1;
                } else if (temp_r23 == 0x3B) {
                    var_r15 = 1;
                    eventObject = fn_80201814(fn_80200C20(arg2));
                    if ((eventObject != NULL) && (fn_80036E50(eventObject) == 6)) {
                        var_r15 = 0;
                    }
                    if (arg3 != NULL) {
                        *arg3 = var_r15;
                    }
                    return 1;
                } else if (temp_r23 == 0x4E) {
                    if (arg3 != NULL) {
                        if ((s32) M2C_FIELD(temp_r27, s32 *, 0x6C) != 0) {
                            var_r0_2 = 0;
                        } else {
                            var_r0_2 = 1;
                        }
                        *arg3 = var_r0_2;
                    }
                    return 1;
                } else if (temp_r23 == 0x82) {
                    if (arg3 != NULL) {
                        *arg3 = 1;
                    }
                    return 1;
                } else if (temp_r23 == 0x32) {
                    fn_80066A0C(arg0, arg2);
                    return 1;
                } else if (temp_r23 == 0xE6) {
                    fn_80066888(temp_r31, fn_80200C38(arg2), lbl_8064E614, lbl_8064E618);
                    return 1;
                } else if (temp_r23 == 0x35) {
                    temp_r15_4 = fn_80200C38(arg2);
                    temp_r3_5 = fn_801A7488(temp_r15_4);
                    if (temp_r3_5 == 0xB) {
                        fn_801A7470(temp_r15_4, 0xD);
                    } else if (temp_r3_5 == 0xC) {
                        fn_801A7470(temp_r15_4, 0xE);
                    }
                    fn_80066754(arg0, arg2, arg3);
                    fn_801A7470(temp_r15_4, temp_r3_5);
                    if ((temp_r3_5 == 0xB) || (temp_r3_5 == 0xC)) {
                        fn_801296F8(temp_r31, 0x1FD70);
                    }
                    return 1;
                } else if (temp_r23 == 0xEA) {
                    fn_800674E4(arg0, arg2);
                    if ((s32) lbl_8064D18C == 0x88) {
                        temp_r3_6 = M2C_FIELD(temp_r27, s16 *, 0xEA);
                        M2C_FIELD(temp_r27, s16 *, 0xEA) = (s16)(((s16)temp_r3_6 >> 1) < 1 ? 1 : (temp_r3_6 >> 1));
                        temp_r3_7 = M2C_FIELD(temp_r27, s16 *, 0xFA);
                        M2C_FIELD(temp_r27, s16 *, 0xFA) = (s16)(((s16)temp_r3_7 >> 1) < 1 ? 1 : (temp_r3_7 >> 1));
                        temp_r3_8 = M2C_FIELD(temp_r27, s16 *, 0xFC);
                        M2C_FIELD(temp_r27, s16 *, 0xFC) = (s16)(((s16)temp_r3_8 >> 1) < 1 ? 1 : (temp_r3_8 >> 1));
                        temp_r3_9 = M2C_FIELD(temp_r27, s16 *, 0xEE);
                        M2C_FIELD(temp_r27, s16 *, 0xEE) = (s16)(((s16)temp_r3_9 >> 1) < 1 ? 1 : (temp_r3_9 >> 1));
                        temp_r3_10 = M2C_FIELD(temp_r27, s16 *, 0xF0);
                        M2C_FIELD(temp_r27, s16 *, 0xF0) = (s16)(((s16)temp_r3_10 >> 1) < 1 ? 1 : (temp_r3_10 >> 1));
                        temp_r3_11 = M2C_FIELD(temp_r27, s16 *, 0xEC);
                        M2C_FIELD(temp_r27, s16 *, 0xEC) = (s16)(((s16)temp_r3_11 >> 1) < 1 ? 1 : (temp_r3_11 >> 1));
                        fn_80038308((void *)arg0, 0, &sp10);
                        fn_800389E0(arg0, 0, (s16)(((s16)sp10 >> 1) < 1 ? 1 : (sp10 >> 1)), 0);
                        M2C_FIELD(temp_r28, s16 *, 0x86) = (s16) (M2C_FIELD(temp_r28, s16 *, 0x86) + 0x1E);
                    } else if ((s32) lbl_8064D18C == 0x29) {
                        M2C_FIELD(temp_r28, s16 *, 0x86) = (s16) (M2C_FIELD(temp_r28, s16 *, 0x86) + 0x1E);
                    }
                    return 1;
                } else if (temp_r23 == 0xEB) {
                    fn_80067650(arg0, arg2);
                    return 1;
                } else if (temp_r23 == 0xF3) {
                    fn_800EA0FC(arg0, temp_r27, fn_80200C38(arg2), arg2, arg3);
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x1) {
            do {
                if (temp_r23 == 0x1) {
                    fn_8011F778(temp_r31, lbl_8064E61C);
                    fn_8011F788(temp_r31, lbl_8064E61C);
                    fn_8011F798(temp_r31, lbl_8064E61C);
                    return 1;
                } else if (temp_r23 == 0x5A) {
                    eventObject = fn_80201814(fn_80200C20(arg2));
                    if (eventObject != NULL) {
                        var_r15_2 = (u32)fn_80201BC8(eventObject);
                    } else {
                        var_r15_2 = 0U;
                    }
                    if ((var_r15_2 != 0U) && (fn_800460EC() == 0) && (fn_800CAF7C(arg0) != 0) && (M2C_FIELD(M2C_FIELD(temp_r21, void **, 0x8C), s16 *, 0x150) == 0)) {
                        fn_8011F114(&sp50, (void *)var_r15_2);
                        vec74 = vec50;
                        temp_r6 = M2C_FIELD(temp_r27, s16 *, 0x14A);
                        if ((fn_80204434(temp_r31, &sp74, 0, lbl_8064E620 * (f32) temp_r6) == 0) && ((s32) lbl_8064D18C != 0x34)) {
                            fn_8011F114(&sp44, (void *)var_r15_2);
                            M2C_FIELD(temp_r27, Fn800614A8Vec *, 0x94) = vec44;
                            if (fn_8011F598(var_r15_2, 0, 0, -1, &searchResult.second, 1) != -1) {
                                fn_8012FE10(var_r15_2, 0, &sp80);
                            } else {
                                vec80 = vec74;
                            }
                            if (((s32) M2C_FIELD(temp_r21, s32 *, 0x94) == 1) && (fn_8012FF34(temp_r31, &sp80, 4, 4) != 0)) {
                                fn_801302BC(temp_r31, 0x3C);
                            }
                            fn_80201D2C((void *)arg0, 0x15);
                            fn_80201D14((void *)arg0, 1);
                        }
                    }
                    return 1;
                } else if (temp_r23 == 0x3) {
                    fn_80060C24(temp_r31, temp_r20, temp_r19);
                    fn_80060D4C(arg0, temp_r31, arg2, temp_r20, temp_r19);
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x15) {
            do {
                if (temp_r23 == 0x1) {
                    M2C_FIELD(temp_r27, f32 *, 0xC4) = (f32) lbl_8064E5DC;
                    fn_8012B344((void *)temp_r31);
                    return 1;
                } else if (temp_r23 == 0x3) {
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    if (fn_80060D4C(arg0, temp_r31, arg2, temp_r20, temp_r19) == 0) {
                        if (fn_800BE86C(temp_r31, (s8 *)temp_r27 + 0x94, 2, 0, lbl_8064E608) == 0) {
                            fn_801294DC(temp_r31, 0xF, 0x25, 1);
                            fn_80201D2C((void *)arg0, 1);
                            fn_80201D14((void *)arg0, 1);
                        } else {
                            temp_f2 = M2C_FIELD(temp_r27, f32 *, 0xC4);
                            if (temp_f2 < lbl_8064E624) {
                                M2C_FIELD(temp_r27, f32 *, 0xC4) = (f32) (temp_f2 + lbl_8064E628);
                                if ((temp_f2 <= lbl_8064E614) && (M2C_FIELD(temp_r27, f32 *, 0xC4) > lbl_8064E614)) {
                                    fn_801A977C(temp_r31, 0x3F);
                                }
                            }
                        }
                    }
                    return 1;
                } else if (temp_r23 == 0x5A) {
                    eventObject = fn_80201814(fn_80200C20(arg2));
                    if (eventObject != NULL) {
                        var_r15_3 = (u32)fn_80201BC8(eventObject);
                    } else {
                        var_r15_3 = 0U;
                    }
                    if ((var_r15_3 != 0U) && (fn_800460EC() == 0) && (fn_800CAF7C(arg0) != 0) && (M2C_FIELD(temp_r27, s16 *, 0x150) == 0)) {
                        fn_8011F114(&sp38, (void *)var_r15_3);
                        vec68 = vec38;
                        temp_r6_2 = M2C_FIELD(temp_r27, s16 *, 0x14A);
                        if ((fn_80204434(temp_r31, &sp68, 0, lbl_8064E620 * (f32) temp_r6_2) == 0) && ((s32) lbl_8064D18C != 0x34)) {
                            fn_8011F114(&sp2C, (void *)var_r15_3);
                            M2C_FIELD(temp_r27, Fn800614A8Vec *, 0x94) = vec2C;
                        }
                    }
                    return 1;
                } else if (temp_r23 == 0x2) {
                    temp_r15_5 = fn_80128EAC(temp_r31);
                    temp_r3_12 = fn_801290D0(temp_r31);
                    if ((temp_r3_12 & 4) && ((temp_r15_5 == 3) || (temp_r15_5 == 2))) {
                        if ((s32) lbl_8064D18C == 0x53) {
                            fn_8012B344((void *)temp_r31);
                        } else {
                            fn_80128F74(temp_r31, temp_r3_12 & 0xFFFFFFFB);
                        }
                    }
                    M2C_FIELD(temp_r27, f32 *, 0xC4) = (f32) lbl_8064E5DC;
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x3) {
            if (temp_r23 == 3) {
                fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                fn_800BE010(arg0, temp_r27);
                if (fn_80201C48(temp_r17) != 0) {
                    fn_800BDEE4(arg0, temp_r27);
                }
                fn_80060F9C(arg0, temp_r31, temp_r26, temp_r27, arg2, temp_r20, temp_r19);
                return 1;
            }
            if (temp_r23 == 0x66) {
                fn_8012B344((void *)temp_r31);
                fn_80201D2C((void *)arg0, 1);
                fn_80201D14((void *)arg0, 1);
                return 1;
            }
            return 0;
        } else if (arg1 == 0x6) {
            do {
                if (temp_r23 == 1) {
                    M2C_FIELD(temp_r28, u8 *, 0x89) = (u8) (M2C_FIELD(temp_r28, u8 *, 0x89) & 0xFE);
                    return 1;
                } else if (temp_r23 == 3) {
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    return 1;
                } else if (temp_r23 == 12) {
                    if (fn_80060F10(arg0, temp_r31, arg2) == 0) {
                        M2C_FIELD(temp_r27, s16 *, 0x150) = 0x5A;
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    }
                    return 1;
                } else if (temp_r23 == 7) {
                    if ((fn_80035FB8(arg0, eventData + 0x1B8, &lbl_8064B508, eventData + 0x1CC, &lbl_8064B510, eventData + 0x1D8) == 0) && (fn_80060F10(arg0, temp_r31, arg2) == 0)) {
                        M2C_FIELD(temp_r27, s16 *, 0x150) = 0x5A;
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    }
                    return 1;
                } else if (temp_r23 == 13) {
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    fn_8012B344((void *)temp_r31);
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x5F) {
            do {
                if (temp_r23 == 0x3) {
                    fn_800C9B74(arg0, temp_r31);
                    return 1;
                } else if (temp_r23 == 0x68) {
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0x2) {
                    fn_800C9AD4(arg0, temp_r31);
                    return 1;
                } else if (temp_r23 == 0x69) {
                    return 1;
                } else if (temp_r23 == 0x65) {
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x56) {
            do {
                if (temp_r23 == 0x3) {
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    return 1;
                } else if (temp_r23 == 0x5) {
                    var_r15_4 = 0;
                    if ((fn_80066D04(arg0, 3) == 0) && (fn_80066D04(arg0, 2) == 0)) {
                        var_r15_4 = 1;
                    }
                    fn_8012B344((void *)temp_r31);
                    fn_802045AC(arg0, &sp5C);
                    fn_80179064((s32) sp8C, (s32) sp90, (s32) sp5C, (s32) sp60);
                    if (var_r15_4 == 0) {
                        var_r15_5 = 1;
                        if ((rand() & 1) && (M2C_FIELD(temp_r28, u8 *, 0x89) & 1)) {
                            temp_r16_3 = fn_801A717C();
                            M2C_FIELD(temp_r28, u8 *, 0x89) = (u8) (M2C_FIELD(temp_r28, u8 *, 0x89) & 0xFE);
                            fn_801A7470(temp_r16_3, 0x10);
                            fn_801A74A0(temp_r16_3, temp_r26);
                            fn_801A74A8(temp_r16_3, temp_r26);
                            fn_801A764C(temp_r16_3, &sp8C);
                            temp_r16_4 = (u32)(fn_8020123C(0x35, temp_r26, temp_r26, temp_r16_3) & 0xFFFFFFFFULL);
                            fn_801A7228(temp_r16_3);
                            if (temp_r16_4 & 1) {
                                var_r15_5 = 0;
                            }
                        }
                        if (var_r15_5 != 0) {
                            fn_80201D2C((void *)arg0, 1);
                            fn_80201D14((void *)arg0, 1);
                        }
                    } else {
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    }
                    return 1;
                } else if (temp_r23 == 0x3D) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_8012B344((void *)temp_r31);
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0x2) {
                    fn_802006D4(temp_r26, temp_r26, 0x56, 5, 0);
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x59) {
            do {
                if (temp_r23 == 0x3) {
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    return 1;
                } else if (temp_r23 == 0x5) {
                    fn_8012B344((void *)temp_r31);
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0x3D) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_8012B344((void *)temp_r31);
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0x2) {
                    fn_802006D4(temp_r26, temp_r26, 0x59, 5, 0);
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x7) {
            do {
                if (temp_r23 == 0x3) {
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    return 1;
                } else if (temp_r23 == 0x36) {
                    fn_80201D2C((void *)arg0, 1);
                    fn_80201D14((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0x7) {
                    if (fn_80035FB8(arg0, eventData + 0x1F0, &lbl_8064B518, eventData + 0x1CC, &lbl_8064B510, eventData + 0x1D8) == 0) {
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    }
                    return 1;
                } else if (temp_r23 == 0x35) {
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x20) {
            do {
                if (temp_r23 == 0x3) {
                    fn_8005FD84(temp_r26, arg0, temp_r31, temp_r21, temp_r28);
                    return 1;
                } else if (temp_r23 == 0x5) {
                    temp_r16_5 = fn_80128EAC(temp_r31);
                    temp_r15_6 = fn_801290D0(temp_r31);
                    if ((fn_80128E30(temp_r31) != 0U) && (temp_r16_5 == 0xF) && (temp_r15_6 & 1)) {
                        fn_8012B344((void *)temp_r31);
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    } else {
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    }
                    return 1;
                } else if (temp_r23 == 0x7) {
                    if (fn_80035FB8(arg0, eventData + 0x1F0, &lbl_8064B51C, eventData + 0x1CC, &lbl_8064B510, eventData + 0x1D8) == 0) {
                        fn_80201D2C((void *)arg0, 1);
                        fn_80201D14((void *)arg0, 1);
                    }
                    return 1;
                } else if (temp_r23 == 0x3D) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_800BD2DC(arg0, temp_r27);
                    fn_8020123C(5, temp_r26, temp_r26, 0);
                    return 1;
                } else if (temp_r23 == 0x2) {
                    fn_802006D4(temp_r26, temp_r26, 0x20, 5, 0);
                    return 1;
                } else if (temp_r23 == 0x35) {
                    return 1;
                } else if (temp_r23 == 0x67) {
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x8) {
            if (temp_r23 == 1) {
                fn_80128EAC(temp_r31);
                fn_801290D0(temp_r31);
                fn_80201350(arg0, 0);
                fn_800E0708(arg0, fn_800CA13C(M2C_FIELD(temp_r21, u8 *, 0x9F)) * 2, 0);
                fn_800CC860(arg0, 1, 0);
                fn_800BE8D4(temp_r26);
                fn_800CA2C8(arg0);
                return 1;
            }
            if (temp_r23 == 3) {
                temp_r15_7 = fn_80128EAC(temp_r31);
                fn_801290D0(temp_r31);
                if (temp_r15_7 != 0x18) {

                }
                fn_8003E5DC(arg0, temp_r31, temp_r26, temp_r27);
                return 1;
            }
            if (temp_r23 == 0x3D) {
                fn_800EA3A0(arg0, temp_r27);
                fn_8020123C(0x39, temp_r26, temp_r26, 0);
                return 1;
            }
            if (temp_r23 == 0xC1) {
                if (arg3 != NULL) {
                    *arg3 = fn_800C9BA8(temp_r31, temp_r21);
                }
                return 1;
            }
            if (temp_r23 == 0x2F) {
                fn_80201D2C((void *)arg0, 0x1F);
                fn_80201D14((void *)arg0, 1);
                return 1;
            }
            if (temp_r23 == 0xC2) {
                fn_800CA1BC(arg0, temp_r31, arg2, arg3);
                return 1;
            }
            if (temp_r23 == 0x11) {
                if (fn_8003C04C(arg0) != 0) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_800CF598(arg0);
                    fn_80120AD0(temp_r31, 0, 0, 0x101, lbl_8064E62C, lbl_8064E5DC);
                    fn_801294DC(temp_r31, 0x28, 0x21, 0xA);
                    fn_80201D34((void *)arg0, 0x15);
                    fn_80201D1C((void *)arg0, 1);
                }
                return 1;
            }
            if (temp_r23 == 0xB) {
                temp_r15_8 = fn_80200C38(arg2);
                if (fn_801A74C0(temp_r15_8) & 0x20) {
                    temp_r15_9 = fn_800654F8(temp_r15_8);
                    fn_8020123C(0x2F, temp_r26, temp_r26, 0);
                    fn_8020104C(0x31, (void *)temp_r26, (void *)temp_r26, 0, lbl_8064E630);
                    if (arg3 != NULL) {
                        *arg3 = temp_r15_9;
                    }
                }
                return 1;
            }
            if (temp_r23 == 0x35) {
                fn_80066888(temp_r31, fn_80200C38(arg2), lbl_8064E614, lbl_8064E618);
                return 1;
            }
            do {
                if (temp_r23 == 0x4E) {
                    if (arg3 != NULL) {
                        *arg3 = 0;
                    }
                    return 1;
                } else if (temp_r23 == 0x33) {
                    fn_8020123C(0x39, temp_r26, temp_r26, 0);
                    return 1;
                } else if (temp_r23 == 0x2) {
                    fn_802006D4(temp_r26, temp_r26, 8, 0x11, 0);
                    return 1;
                } else if (temp_r23 == 0x3B) {
                    return 1;
                } else if (temp_r23 == 0x8) {
                    return 1;
                } else if (temp_r23 == 0x35) {
                    return 1;
                } else if (temp_r23 == 0x32) {
                    return 1;
                } else if (temp_r23 == 0xB) {
                    return 1;
                } else if (temp_r23 == 0x27) {
                    return 1;
                } else if (temp_r23 == 0x67) {
                    return 1;
                } else if (temp_r23 == 0xEA) {
                    return 1;
                }
            } while (0);
            break;
        } else if (arg1 == 0x1F) {
            do {
                if (temp_r23 == 0x1) {
                    fn_80128EAC(temp_r31);
                    fn_801290D0(temp_r31);
                    fn_800BE8D4(temp_r26);
                    fn_800CC860(arg0, 2, 3);
                    fn_801A977C(temp_r31, 0x33);
                    fn_800CA2C8(arg0);
                    fn_80204FDC(arg0);
                    fn_8020104C(0x11, (void *)temp_r26, (void *)temp_r26, 0, lbl_8064E634);
                    return 1;
                } else if (temp_r23 == 0x30) {
                    temp_r3_13 = fn_800654F8(fn_80200C38(arg2));
                    if (arg3 != NULL) {
                        *arg3 = temp_r3_13;
                    }
                    return 1;
                } else if (temp_r23 == 0x31) {
                    fn_8003C114(arg0, temp_r31, temp_r26);
                    return 1;
                } else if (temp_r23 == 0x3D) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_8020123C(0x39, temp_r26, temp_r26, 0);
                    return 1;
                } else if (temp_r23 == 0x11) {
                    fn_800EA3A0(arg0, temp_r27);
                    fn_800CF598(arg0);
                    fn_80120AD0(temp_r31, 0, 0, 0x101, lbl_8064E62C, lbl_8064E5DC);
                    fn_80201D34((void *)arg0, 0x15);
                    fn_80201D1C((void *)arg0, 1);
                    return 1;
                } else if (temp_r23 == 0x4E) {
                    if (arg3 != NULL) {
                        *arg3 = 0;
                    }
                    return 1;
                } else if (temp_r23 == 0x3B) {
                    return 1;
                } else if (temp_r23 == 0x8) {
                    return 1;
                } else if (temp_r23 == 0x35) {
                    return 1;
                } else if (temp_r23 == 0x32) {
                    return 1;
                } else if (temp_r23 == 0xB) {
                    return 1;
                } else if (temp_r23 == 0x27) {
                    return 1;
                } else if (temp_r23 == 0x67) {
                    return 1;
                } else if (temp_r23 == 0xEA) {
                    return 1;
                }
            } while (0);
            break;
        } else {
            return 0;
        }
    } while (0);
}
