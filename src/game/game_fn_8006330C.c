typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#pragma use_lmw_stmw on

extern s32 lbl_8064C4E0;
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
extern f32 lbl_8064E63C;
extern f32 lbl_8064E640;
extern f32 lbl_8064E644;
extern f32 lbl_8064E648;
extern unsigned char lbl_802FC5BC[];
extern void fn_80204810(void);

s32 fn_800359A0(s32, s32);                   /* extern */
s32 fn_8003D7B4(s32);                        /* extern */
s32 fn_8003DED0(s32, s32, void *);           /* extern */
s32 fn_80048708(s32);                        /* extern */
s32 fn_80064B38(s32, s32, u32 *);            /* extern */
u32 fn_800654F8(s32);                               /* extern */
s32 fn_800674E4(s32, s32);                   /* extern */
s32 fn_80067650(s32, s32);                   /* extern */
s32 fn_80067A18(s32);                        /* extern */
s32 fn_80068290(s32, s32, u32 *);                   /* extern */
s32 fn_80068994(s32, s32);                   /* extern */
s32 fn_80072354(s32);                        /* extern */
s32 fn_800BD2DC(s32, void *);                /* extern */
s32 fn_8011F114();          /* extern */
s32 fn_8011F778(s32, f32);                   /* extern */
unsigned int fn_8011FA8C(s32, s32, s32); /* extern */
s32 fn_8011FF38();                                  /* extern */
s32 fn_80128C28();            /* extern */
void *fn_801294DC(void *, s32, s32, s32);          /* extern */
#define fn_801294DC(a, b, c, d) fn_801294DC((void *)(a), (b), (c), (d))
s32 fn_8012B324(s32);                        /* extern */
s32 fn_8012B344();                        /* extern */
s32 fn_8014D100(s32, void *, s32, s32);       /* extern */
s32 fn_8016B400(s32, s32, s32);              /* extern */
s32 fn_801A5910(s32);                         /* extern */
s32 fn_801A717C();                                  /* extern */
s32 fn_801A7228(s32);                        /* extern */
s32 fn_801A74A0(s32, s32);                   /* extern */
s32 fn_801A74A8(s32, s32);                   /* extern */
s32 fn_801A7518(s32, s16);                   /* extern */
s32 fn_801A7538(s32, s32);            /* extern */
s32 fn_801A764C(s32, f32 *);                  /* extern */
s32 fn_801AAE68(f32, s32, s32, s32, f32 *, s32, s32, s32, u16, s32); /* extern */
s32 fn_801E7974(s32, s32);                   /* extern */
s32 fn_801E79A0(s32, s32);                   /* extern */
s32 fn_801E8328(s32, s32);            /* extern */
s32 fn_80200C10(s32);                               /* extern */
s32 fn_80200C20(s32);                               /* extern */
s32 fn_80200C28(s32);                               /* extern */
s32 fn_80200C38(s32);                               /* extern */
s32 fn_8020104C(s32, s32, s32, s32, f32); /* extern */
s32 fn_8020123C();  /* extern */
s32 fn_80201814();                               /* extern */
s32 fn_80201B54();                               /* extern */
void *fn_80201B8C();                             /* extern */
s32 fn_80201B94(s32);                        /* extern */
s32 fn_80201BC8();                               /* extern */
s32 fn_80201D14();            /* extern */
s32 fn_80201D1C(s32, s32);            /* extern */
s32 fn_80201D2C();            /* extern */
s32 fn_80201D34(s32, s32);                   /* extern */
s32 fn_80204508(s32, s32);                   /* extern */

s32 fn_8006330C(s32 arg0, s32 arg1, s32 arg2, u32 *arg3) {
    s32 sp8;
    f32 sp10[3];
    s16 temp_r0;
    s32 temp_r0_2;
    s32 temp_r25;
    s16 phi_r26;
    u32 temp_r25_2;
    s32 temp_r26;
    s32 temp_r28;
    s32 temp_r28_2;
    void *temp_r27;
    void *temp_r31;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r30_3;

    temp_r26 = fn_80200C10(arg2);
    temp_r25 = fn_80201BC8(arg0);
    temp_r27 = fn_80201B8C(arg0);
    temp_r31 = M2C_FIELD(temp_r27, void **, 0x8C);
    fn_80201B94(arg0);
    temp_r30 = fn_80201B54(arg0);
    fn_8011F114(sp10, temp_r25);
    if (temp_r26 == 3) {
        fn_8003DED0(arg0, temp_r25, temp_r31);
    }
    if (arg1 == 0) {
        if (temp_r26 == 1) {
            fn_8011F778(temp_r25, lbl_8064E644);
            fn_80201D2C(arg0, 0x19);
            fn_80201D14(arg0, 1);
            return 1;
        }
        if (temp_r26 == 0x86) {
            fn_801A5910(fn_80200C38(arg2));
            return 1;
        }
        if (temp_r26 == 0xBB) {
            temp_r30_2 = fn_80200C38(arg2);
            if (temp_r30_2 != 0) {
                fn_801E7974(lbl_8064C4E0, temp_r30_2);
            }
            return 1;
        }
        if (temp_r26 == 0xBC) {
            temp_r30_2 = fn_80200C38(arg2);
            if (temp_r30_2 != 0) {
                fn_801E79A0(lbl_8064C4E0, temp_r30_2);
            }
            return 1;
        }
        if (temp_r26 == 0xBE) {
            temp_r30_2 = fn_80200C38(arg2);
            if (temp_r30_2 != 0) {
                fn_8016B400(temp_r30_2, temp_r30, 0);
            }
            return 1;
        }
        if (temp_r26 == 0x39) {
            fn_8012B324(temp_r25);
            fn_8003D7B4(temp_r30);
            fn_8011FA8C(temp_r25, 0xC0, 0);
            fn_80201D34(arg0, 0);
            fn_80201D1C(arg0, 1);
            fn_8020123C(0x26, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), 0);
            fn_801E8328(2, arg0);
            return 1;
        }
        if (temp_r26 == 0xEA) {
            if ((u8) M2C_FIELD(temp_r27, u8 *, 0x9F) != 0x25U) {
                fn_800674E4(arg0, arg2);
            }
            return 1;
        }
        if (temp_r26 == 0xEB) {
            fn_80067650(arg0, arg2);
            return 1;
        }
        if (temp_r26 == 0xC9) {
            if (fn_8011FF38() != 0) {
                fn_8011FA8C(temp_r25, 0, 0x20000000);
                sp8 = 0;
                fn_801AAE68(lbl_8064E648, 0x1F1, 0x64, 0, sp10, 2, 2, 0,
                            (u16)lbl_8064D18C, sp8);
            }
            return 1;
        }
        if (temp_r26 == 0x3D) {
            fn_800BD2DC(arg0, temp_r31);
            fn_8003D7B4(temp_r30);
            fn_80067A18(temp_r30);
            fn_8020123C(0x26, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), 0);
            fn_8020123C(0x26, temp_r30, temp_r30, 0);
            return 1;
        }
        if (temp_r26 == 0xED) {
            temp_r30 = fn_80200C38(arg2);
            temp_r28 = fn_80200C28(arg2);
            fn_8020123C(0xB, fn_80200C20(arg2), temp_r28, temp_r30);
            fn_801A7228(fn_80200C38(arg2));
            return 1;
        }
        if (temp_r26 == 0x3A) {
            temp_r30 = fn_80200C38(arg2);
            temp_r28 = fn_80200C28(arg2);
            fn_8020123C(0x27, fn_80200C20(arg2), temp_r28, temp_r30);
            fn_801A7228(fn_80200C38(arg2));
            return 1;
        }
        if (temp_r26 == 0xB) {
            fn_800359A0(arg0, fn_80201814(fn_80200C20(arg2)));
            temp_r0_2 = fn_800654F8(fn_80200C38(arg2));
            if (arg3 != 0U) {
                *arg3 = temp_r0_2;
            }
            return 1;
        }
        if (temp_r26 == 0x3F) {
            if (fn_80068290(arg0, arg2, arg3) != 0) {
                fn_8020123C(0x26, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), 0);
                M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
                M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            }
            return 1;
        }
        if (temp_r26 == 0x20) {
            if (arg3 != 0U) {
                *arg3 = 0;
            }
            return 1;
        }
        if (temp_r26 == 0x3B) {
            if (arg3 != 0U) {
                *arg3 = 1;
            }
            return 1;
        }
        if (temp_r26 == 0x4E) {
            if (((u8) M2C_FIELD(temp_r27, u8 *, 0x9E) != 1U) && (arg3 != 0U)) {
                *arg3 = (u32) (M2C_FIELD(temp_r31, s32 *, 0x6C) == 0);
            }
            return 1;
        }
        if (temp_r26 == 0xE) {
            fn_80068994(arg0, arg2);
            return 1;
        }
        if (temp_r26 == 0x27) {
            fn_80064B38(arg0, arg2, arg3);
            return 1;
        }
        if (temp_r26 == 8) {
            fn_8012B344(temp_r25);
            fn_8020123C(0x26, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), 0);
            fn_8020104C(8, fn_80200C20(arg2), temp_r30, 0, lbl_8064E640);
            fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
            fn_80201D1C(arg0, 1);
            M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            return 1;
        }
        goto block_110;
    }
    if (arg1 == 0x19) {
        if (temp_r26 == 0x21) {
            fn_80204508(fn_80201814(M2C_FIELD(temp_r31, s32 *, 0x14)), arg0);
            if ((s8) M2C_FIELD(temp_r31, u8 *, 0x160) == 0) {

            }
            if (fn_801294DC(temp_r25,
                           (s8) M2C_FIELD(temp_r31, u8 *, 0x160) == 0 ? 0x5A : 0x60,
                           0x25, 6) != 0U) {
                fn_80201D2C(arg0, 0x1B);
                fn_80201D14(arg0, 1);
            } else {
                fn_8020123C(0x26, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), 0);
                fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
                fn_80201D1C(arg0, 1);
                M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
                M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            }
            return 1;
        }
        if (temp_r26 == 0x26) {
            fn_8012B344(temp_r25);
            fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
            fn_80201D1C(arg0, 1);
            M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            return 1;
        }
        goto block_110;
    }
    if (arg1 == 0x1B) {
        if (temp_r26 == 1) {
            return 1;
        }
        if (temp_r26 == 0x24) {
            fn_8012B344(temp_r25);
            fn_8011F778(temp_r25, lbl_8064E63C);
            fn_80048708(temp_r25);
            fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
            fn_80201D1C(arg0, 1);
            M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            return 1;
        }
        if (temp_r26 == 0x26) {
            fn_8012B344(temp_r25);
            fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
            fn_80201D1C(arg0, 1);
            M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            return 1;
        }
        if (temp_r26 == 0x25) {
            fn_80204508(fn_80201814(M2C_FIELD(temp_r31, s32 *, 0x14)), arg0);
            if ((s8) M2C_FIELD(temp_r31, u8 *, 0x160) == 0) {

            }
            temp_r25_2 = (u32)fn_801294DC(temp_r25,
                                    (s8) M2C_FIELD(temp_r31, u8 *, 0x160) == 0 ? 0x5C : 0x62,
                                    0x20, 8);
            if (temp_r25_2 != 0) {
                fn_80128C28(temp_r25_2, fn_80204810, (temp_r30 << 8) | 0x22);
                fn_80201D2C(arg0, 0x1D);
                fn_80201D14(arg0, 1);
                M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
            } else {
                fn_8020123C(0x26, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), 0);
                fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
                fn_80201D1C(arg0, 1);
                M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
                M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            }
            return 1;
        }
        if (temp_r26 == 3) {
            temp_r28 = 3;
            if ((u8) M2C_FIELD(temp_r27, u8 *, 0x9E) == 1U) {
                temp_r28 = 7;
            }
            if ((lbl_8064D5A8 & 0xF) == 0) {
                fn_8014D100(temp_r25, lbl_802FC5BC + 0x18, 2, 1);
            }
            if ((lbl_8064D5A8 & temp_r28) == 0) {
                fn_80072354(M2C_FIELD(temp_r27, s32 *, 0x90));
                temp_r25_2 = fn_801A717C();
                temp_r0 = M2C_FIELD(temp_r27, s16 *, 0x98);
                phi_r26 = 1;
                if (temp_r0 < 0x43) {
                    if (temp_r0 < 0x40) {

                    } else {
                        phi_r26 = 0;
                    }
                }
                fn_801A74A0(temp_r25_2, temp_r30);
                fn_801A74A8(temp_r25_2, M2C_FIELD(temp_r31, s32 *, 0x14));
                fn_801A7538(temp_r25_2, 1);
                fn_801A7518(temp_r25_2, phi_r26);
                fn_801A764C(temp_r25_2, sp10);
                fn_8020123C(0x27, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), temp_r25_2);
                temp_r0_2 = M2C_FIELD(temp_r27, s32 *, 0x94);
                if (temp_r0_2 == 2) {
                    fn_801A7538(temp_r25_2, 4);
                    fn_801A7518(temp_r25_2, (s16) ((s16) phi_r26 * 2));
                    fn_8020123C(0x27, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), temp_r25_2);
                } else if (temp_r0_2 == 3) {
                    fn_801A7538(temp_r25_2, 2);
                    fn_801A7518(temp_r25_2, phi_r26);
                    fn_8020123C(0x27, temp_r30, M2C_FIELD(temp_r31, s32 *, 0x14), temp_r25_2);
                }
                fn_801A7228(temp_r25_2);
            }
            return 1;
        }
        goto block_110;
    }
    if (arg1 == 0x1D) {
        if (temp_r26 == 0x22) {
            fn_8011F778(temp_r25, lbl_8064E63C);
            fn_80048708(temp_r25);
            fn_8020104C(0x37, M2C_FIELD(temp_r31, s32 *, 0x14), temp_r30, 0, lbl_8064E640);
            fn_80201D34(arg0, M2C_FIELD(temp_r31, s32 *, 0x18));
            fn_80201D1C(arg0, 1);
            M2C_FIELD(temp_r31, s32 *, 0x14) = 0;
            M2C_FIELD(temp_r31, s32 *, 0x18) = 0;
            return 1;
        }
        if (temp_r26 == 0x3D) {
            fn_8012B344(temp_r25);
            fn_8020123C(0x22, temp_r30, temp_r30, 0);
            fn_8003D7B4(temp_r30);
            fn_80067A18(temp_r30);
            fn_800BD2DC(arg0, temp_r31);
            return 1;
        }
block_110:
        return 0;
    }
    return 0;
}
