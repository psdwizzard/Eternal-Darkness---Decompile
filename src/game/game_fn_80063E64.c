typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

#define NULL ((void *)0)
typedef struct RuntimeState {
    u8 pad_00[0x14];
    s32 target;
    s32 pending;
    u8 pad_1C[0x50];
    s32 status;
    u8 pad_70[0xF5];
    u8 cycle;
} RuntimeState;

typedef struct ContextState {
    u8 pad_00[0x8C];
    RuntimeState *runtime;
    u8 pad_90[0xE];
    u8 mode;
} ContextState;

s32 fn_800359A0(s32, u32);                      /* extern */
s32 fn_80036E14(s32);                               /* extern */
s32 fn_8003D7B4(s32);                           /* extern */
s32 fn_8003DED0(s32, u32, void *);              /* extern */
s32 fn_80048708(u32);                           /* extern */
s32 fn_80063124(s32, u32, s32, s32, void *, s32 *); /* extern */
s32 fn_80063D60(void *, void *, u8);                 /* extern */
s32 fn_800654F8();                                  /* extern */
s32 fn_800674E4(s32, s32);                      /* extern */
s32 fn_80067650(s32, s32);                      /* extern */
s32 fn_80067A18(s32);                           /* extern */
s32 fn_80068290(s32, s32, s32 *);                   /* extern */
s32 fn_80068994(s32, s32);                      /* extern */
s32 fn_8006D3E4(s32, s32);                  /* extern */
s32 fn_800BD2DC(s32, void *);                   /* extern */
s32 fn_800C65FC(s32);                           /* extern */
s32 fn_8011E310(s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 fn_8011E800(s32);                       /* extern */
s32 fn_8011F114();                /* extern */
s32 fn_8011F778(u32, f32);                      /* extern */
unsigned int fn_8011FA8C(u32, s32, s32);         /* extern */
s32 fn_8011FB4C(u32);                               /* extern */
s32 fn_8011FF38();                                  /* extern */
s32 fn_801287C4(u32, s32 *, s32, s32);      /* extern */
s32 fn_80128C28();                /* extern */
s32 fn_80128C44(u32, s32 *, s32);           /* extern */
void *fn_801294DC(void *, s32, s32, s32);    /* extern */
#define fn_801294DC(a, b, c, d) fn_801294DC((void *)(a), (b), (c), (d))
s32 fn_8012A1FC(u32, s32);                      /* extern */
s32 fn_8012B324(u32);                           /* extern */
s32 fn_8012B344();                           /* extern */
s32 fn_8012C62C(); /* extern */
s32 fn_8012F58C(u32, s32, s32, s32, s32, s32); /* extern */
s32 fn_80157E1C();                                  /* extern */
s32 fn_80157E24(s32, s32);                      /* extern */
s32 fn_80158598(s32, s32);                      /* extern */
u32 fn_8015C910();                                  /* extern */
s32 fn_8016B400(s32, s32, s32);             /* extern */
s32 fn_801A5910();                              /* extern */
s32 fn_801A7228();                              /* extern */
s32 fn_801AAE68(s32, s32, s32, s32 *, s32, s32, s32, u16, s32, f32); /* extern */
s32 fn_801E741C(s32 *);                         /* extern */
s32 fn_801E7974(s32, s32);                      /* extern */
s32 fn_801E79A0(s32, s32);                      /* extern */
s32 fn_801E8328(s32, s32);                  /* extern */
u16 fn_801F6228(s32, s32, s32);             /* extern */
s32 fn_801F63E4(s32, s32);                  /* extern */
s32 fn_80200C10(s32);                               /* extern */
s32 fn_80200C20(s32);                               /* extern */
s32 fn_80200C28(s32);                               /* extern */
s32 fn_80200C38(s32);                               /* extern */
s32 fn_8020104C(s32, s32, s32, s32, f32); /* extern */
s32 fn_8020123C();        /* extern */
u32 fn_80201814();                               /* extern */
s32 fn_80201B44();                                  /* extern */
s32 fn_80201B54();                               /* extern */
void *fn_80201B8C();                             /* extern */
u32 fn_80201BC8();                               /* extern */
s32 fn_80201D14();                  /* extern */
s32 fn_80201D1C(s32, s32);                  /* extern */
s32 fn_80201D2C();                  /* extern */
s32 fn_80201D34();                      /* extern */
s32 fn_80204508(s32, u32);                      /* extern */
extern s32 fn_80063030[];
extern s32 fn_80204810[];
extern s32 lbl_80243E38[];
extern s32 lbl_8064C4E0;
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
extern f32 lbl_8064E63C;
extern f32 lbl_8064E640;
extern f32 lbl_8064E644;
extern f32 lbl_8064E648;
extern s32 lbl_8064E64C;
extern s32 lbl_8064E650;
extern s32 lbl_8064E654;
extern s32 lbl_8064E658;
extern s32 lbl_8064E65C;
extern s32 lbl_8064E660;
extern s32 lbl_8064E664;
extern s32 lbl_8064E668;
extern s32 lbl_8064E66C;
extern s32 lbl_8064E670;
extern s32 lbl_8064E674;
extern s32 lbl_8064E678;
extern s32 lbl_8064E67C;
extern s32 lbl_8064E680;
extern s32 lbl_8064E684;
extern s32 lbl_8064E688;
extern s32 lbl_8064E68C;
extern s32 lbl_8064E690;
extern f32 lbl_8064E694;

s32 fn_80063E64(s32 context, s32 state, s32 event, s32 *result) {
    s32 sp58[3];
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 context_data_2;
    s32 context_data_3;
    s32 event_type;
    s32 event_type_2;
    s32 current_mode;
    s32 current_mode_2;
    s32 temp_r26;
    s32 temp_r26_2;
    s32 temp_r26_3;
    s32 temp_r26_4;
    s32 temp_r26_5;
    s32 temp_r28;
    s32 temp_r28_2;
    RuntimeState *object_state;
    u32 runtime;
    s32 owner;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_5;
    s32 var_r24;
    s32 var_r24_2;
    s32 var_r24_3;
    u32 temp_r3_4;
    u32 temp_r3_6;
    ContextState *context_data;

    event_type = fn_80200C10(event);
    runtime = fn_80201BC8(context);
    context_data = fn_80201B8C(context);
    object_state = context_data->runtime;
    owner = fn_80201B54(context);
    fn_8011F114(sp58, runtime);
    current_mode = fn_8011FB4C(runtime);
    if (event_type == 3) {
        fn_800C65FC(context);
        fn_8003DED0(context, runtime, object_state);
    }
    if (state == 0) {
        if (event_type == 0x1) {
            fn_8011F778(runtime, lbl_8064E644);
            if (fn_80036E14(context) == 1) {
                fn_8011E800(1);
            }
            fn_80201D2C(context, 0x1A);
            fn_80201D14(context, 1);
            return 1;
        }
        if (event_type == 0xBB) {
            temp_r3 = fn_80200C38(event);
            if (temp_r3 != 0) {
                fn_801E7974(lbl_8064C4E0, temp_r3);
            }
            return 1;
        }
        if (event_type == 0xEA) {
            fn_800674E4(context, event);
            return 1;
        }
        if (event_type == 0xEB) {
            fn_80067650(context, event);
            return 1;
        }
        if (event_type == 0xC9) {
            if (fn_8011FF38() != 0) {
                fn_8011FA8C(runtime, 0, 0x20000000);
                fn_801AAE68(0x1F1, 0x64, 0, sp58, 2, 2, 0, (u16) lbl_8064D18C, 0, lbl_8064E648);
            }
            return 1;
        }
        if (event_type == 0x86) {
            fn_80200C38(event);
            fn_801A5910();
            return 1;
        }
        if (event_type == 0xBC) {
            temp_r3 = fn_80200C38(event);
            if (temp_r3 != 0) {
                fn_801E79A0(lbl_8064C4E0, temp_r3);
            }
            return 1;
        }
        if (event_type == 0xBE) {
            temp_r3 = fn_80200C38(event);
            if (temp_r3 != 0) {
                fn_8016B400(temp_r3, owner, 0);
            }
            return 1;
        }
        if (event_type == 0x39) {
            fn_8012B324(runtime);
            fn_8003D7B4(owner);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_8011FA8C(runtime, 0xC0, 0);
            fn_8020123C(0x26, owner, object_state->target, 0);
            fn_801E8328(2, context);
            return 1;
        }
        if (event_type == 0x66) {
            fn_8020123C(0x26, owner, object_state->target, 0);
            fn_8020123C(0x26, owner, owner, 0);
            return 1;
        }
        if (event_type == 0x3D) {
            fn_800BD2DC(context, object_state);
            fn_8003D7B4(owner);
            fn_80067A18(owner);
            fn_8020123C(0x26, owner, object_state->target, 0);
            fn_8020123C(0x26, owner, owner, 0);
            return 1;
        }
        if (event_type == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_80200C38(event);
            fn_801A7228();
            return 1;
        }
        if (event_type == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_80200C38(event);
            fn_801A7228();
            return 1;
        }
        if (event_type == 0xB) {
            fn_80200C20(event);
            fn_800359A0(context, fn_80201814());
            fn_80200C38(event);
            temp_r3 = fn_800654F8();
            if (result != NULL) {
                *result = temp_r3;
            }
            return 1;
        }
        if (event_type == 0x4E) {
            if (((u8) context_data->mode != 1) && (result != NULL)) {
                *result = object_state->status == 0;
            }
            return 1;
        }
        if (event_type == 0x20) {
            if (result != NULL) {
                *result = 0;
            }
            return 1;
        }
        if (event_type == 0x26) {
            fn_8012B344(runtime);
            if ((s32) object_state->pending != 0) {
                fn_80201D34(context, object_state->pending);
                fn_80201D1C(context, 1);
                object_state->pending = 0;
            }
            object_state->target = 0;
            return 1;
        }
        if (event_type == 0x3B) {
            if (result != NULL) {
                *result = 1;
            }
            return 1;
        }
        if (event_type == 0x3F) {
            if (fn_80068290(context, event, result) != 0) {
                fn_8020123C(0x26, owner, object_state->target, 0);
                object_state->target = 0;
                object_state->pending = 0;
            }
            return 1;
        }
        if (event_type == 0x8A) {
            if (current_mode != (s32) lbl_8064D18C) {
                fn_8020104C(0x8A, owner, owner, 0, lbl_8064E640);
            } else {
                context_data_2 = fn_801E741C(lbl_80243E38);
                sp4C = lbl_8064E654;
                sp50 = lbl_8064E650;
                sp54 = lbl_8064E64C;
                fn_8012C62C(runtime, (s32 *)0xF, &sp54, &sp50, &sp4C, 6);
                if (fn_801F6228(context_data_2, 0, 2) != 0) {
                    fn_801F63E4(context_data_2, 1);
                }
                temp_r3_2 = fn_80158598(owner, 0);
                if (temp_r3_2 != 0) {
                    temp_r26_3 = fn_80157E1C();
                    var_r24 = 0;
                    goto loop_75_check;
loop_75:
                        fn_80157E24(temp_r3_2, var_r24);
                        if ((fn_80201814() != 0U) && ((temp_r3_4 = fn_80201BC8()) != 0U)) {
                            sp40 = lbl_8064E660;
                            sp44 = lbl_8064E65C;
                            sp48 = lbl_8064E658;
                            fn_8012C62C(temp_r3_4, (s32 *)0xF, &sp48, &sp44, &sp40, 6);
                        }
                        var_r24 += 1;
loop_75_check:
                    if (var_r24 < temp_r26_3) {
                        goto loop_75;
                    }
                }
                fn_8020104C(0x8B, owner, owner, 0, lbl_8064E694);
            }
            return 1;
        }
        if (event_type == 0x8B) {
            if (current_mode != (s32) lbl_8064D18C) {
                fn_8020104C(0x8B, owner, owner, 0, lbl_8064E640);
            } else {
                sp34 = lbl_8064E66C;
                sp38 = lbl_8064E668;
                sp3C = lbl_8064E664;
                fn_8012C62C(runtime, (s32 *)0xF, &sp3C, &sp38, &sp34, 6, lbl_8064E668);
                fn_8012F58C(runtime, 0xF, 0, 1, 0x1E, 8);
                temp_r3_3 = fn_80158598(owner, 0);
                if (temp_r3_3 != 0) {
                    temp_r26_4 = fn_80157E1C();
                    var_r24_2 = 0;
                    goto loop_87_check;
loop_87:
                        fn_80157E24(temp_r3_3, var_r24_2);
                        if (fn_80201814() != 0U) {
                            temp_r3_4 = fn_80201BC8();
                            if (temp_r3_4 != 0U) {
                                sp28 = lbl_8064E678;
                                sp2C = lbl_8064E674;
                                sp30 = lbl_8064E670;
                                fn_8012C62C(temp_r3_4, (s32 *)0xF, &sp30, &sp2C, &sp28, 6);
                                fn_8012F58C(temp_r3_4, 0xF, 0, 1, 0x1E, 8);
                            }
                        }
                        var_r24_2 += 1;
loop_87_check:
                    if (var_r24_2 < temp_r26_4) {
                        goto loop_87;
                    }
                }
            }
            return 1;
        }
        if (event_type == 0x8C) {
            if (current_mode != (s32) lbl_8064D18C) {
                fn_8020104C(0x8C, owner, owner, 0, lbl_8064E640);
            } else {
                context_data_3 = fn_801E741C(lbl_80243E38);
                sp1C = lbl_8064E684;
                sp20 = lbl_8064E680;
                sp24 = lbl_8064E67C;
                fn_8012C62C(runtime, (s32 *)0xF, &sp24, &sp20, &sp1C, 6);
                if (fn_801F6228(context_data_3, 0, 2) != 0) {
                    fn_801F63E4(context_data_3, 0);
                }
                temp_r3_5 = fn_80158598(owner, 0);
                if (temp_r3_5 != 0) {
                    temp_r26_5 = fn_80157E1C();
                    var_r24_3 = 0;
                    goto loop_100_check;
loop_100:
                        fn_80157E24(temp_r3_5, var_r24_3);
                        if ((fn_80201814() != 0U) && ((temp_r3_4 = fn_80201BC8()) != 0U)) {
                            sp10 = lbl_8064E690;
                            sp14 = lbl_8064E68C;
                            sp18 = lbl_8064E688;
                            fn_8012C62C(temp_r3_4, (s32 *)0xF, &sp18, &sp14, &sp10, 6);
                        }
                        var_r24_3 += 1;
loop_100_check:
                    if (var_r24_3 < temp_r26_5) {
                        goto loop_100;
                    }
                }
            }
            return 1;
        }
    } else if (state == 0x1A) {
        if (event_type == 3) {
            if ((fn_8015C910() != 0U) && (owner == fn_80201B44())) {
                fn_8020123C(0x66, owner, owner, 0);
            }
            return 1;
        }
        if (event_type == 35) {
            fn_80200C20(event);
            fn_80201814();
            fn_80204508(context, fn_80201814(object_state->target));
            if (fn_801294DC(runtime, 0x25, 0x25, 6) != 0U) {
                fn_80201D2C(context, 0x1C);
                fn_80201D14(context, 1);
            } else {
                fn_8020123C(0x26, owner, object_state->target, 0);
                fn_80201D34(context, object_state->pending);
                fn_80201D1C(context, 1);
                object_state->target = 0;
                object_state->pending = 0;
            }
            return 1;
        }
        if (event_type == 2) {
            if (fn_80036E14(context) == 1) {
                fn_8011E800(0);
            }
            return 1;
        }
    } else if (state == 0x1C) {
        if (event_type == 1) {
            object_state->cycle = 0U;
            return 1;
        }
        if (event_type == 14) {
            fn_80068994(context, event);
            return 1;
        }
        if (event_type == 39) {
            fn_80063124(context, runtime, event, owner, object_state, result);
            return 1;
        }
        if (event_type == 37) {
            fn_80204508(context, fn_80201814(object_state->target));
            current_mode_2 = fn_8012A1FC(runtime, 0x27) + 0x1E;
            temp_r3_6 = (u32)fn_801294DC(runtime, 0x27, 0x24, 8);
            if (temp_r3_6 != 0U) {
                event_type_2 = owner << 8;
                fn_80128C28(fn_80204810, event_type_2 | 6);
                fn_80128C44(temp_r3_6, fn_80204810, event_type_2 | 7);
                fn_801287C4(temp_r3_6, fn_80063030, owner, current_mode_2);
                fn_8020123C(0x25, owner, object_state->target, 0);
                fn_80201D2C(context, 0x7B);
                fn_80201D14(context, 1);
            } else {
                fn_8020123C(0x26, owner, object_state->target, 0);
                fn_80201D34(context, object_state->pending);
                fn_80201D1C(context, 1);
                object_state->target = 0;
                object_state->pending = 0;
            }
            return 1;
        }
        if (event_type == 44) {
            if (fn_8006D3E4(0x40000, 0) == 0) {
                temp_r3_4 = fn_80200C38(event);
                if (temp_r3_4 != 0U) {
                    object_state->cycle = (u8) (object_state->cycle + fn_80063D60((void *)temp_r3_4, context_data, object_state->cycle));
                } else {
                    object_state->cycle = (u8) (object_state->cycle + 1);
                }
                if ((u8) object_state->cycle >= 8U) {
                    object_state->cycle = 0U;
                    fn_8020123C(0x25, owner, owner, 0);
                }
            }
            return 1;
        }
        if (event_type == 3) {
            if (fn_80036E14(context) == 1) {
                fn_8011E310(6, 0x14, 0, 0, 0x32, 1, 0);
            } else if (!(lbl_8064D5A8 & 7)) {
                fn_8020123C(0x2C, owner, owner, 0);
            }
            if ((fn_8015C910() != 0U) && (owner == fn_80201B44())) {
                fn_8020123C(0x66, owner, owner, 0);
            }
            return 1;
        }
    } else if (state == 0x7B) {
        if (event_type == 6) {
            fn_8011F778(runtime, lbl_8064E63C);
            fn_80048708(runtime);
            fn_80201D34(context, object_state->pending);
            fn_80201D1C(context, 1);
            object_state->target = 0;
            object_state->pending = 0;
            return 1;
        }
        if (event_type == 7) {
            fn_8020123C(6, owner, owner, 0);
            return 1;
        }
        if (event_type == 14) {
            fn_80068994(context, event);
            return 1;
        }
        if (event_type == 39) {
            fn_80063124(context, runtime, event, owner, object_state, result);
            return 1;
        }
    } else {
        return 0;
    }
    /* bug: did not emit code for node #156; contents below: */
    /* bug: did not emit code for node #157; contents below: */
    return 0;
}
