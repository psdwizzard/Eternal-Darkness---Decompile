typedef signed int s32;
typedef unsigned char u8;

#pragma use_lmw_stmw on

extern char lbl_80243A40[];
extern char lbl_8064B4E4;
extern char lbl_8064B4FC;
extern s32 lbl_8064B4F8;
extern s32 lbl_8064C86C;
extern s32 lbl_8064D18C;

extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern s32 fn_80054BCC(s32 value);
extern void fn_8011E174(s32 index, s32 value);
extern void fn_801301B0(void *object, s32 set, s32 clear);
extern s32 fn_800460EC(void);
extern void fn_800073D8(s32 value);
extern void fn_802020B4(void *context, s32 value);
extern void fn_80045A24(s32 value, s32 mode);
extern void *fn_801E741C(char *name);
extern s32 fn_80054D14(void *resource, void *context, void *object, s32 force);
extern void fn_80054DF4(void *resource, void *context, void *object, s32 force);
extern void fn_800C4F48(void *context, void *object, void *event, s32 *result);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_801B05E8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 fn_80035FB8(void *context, char *first, char *second, char *third,
                      char *value, char *fourth);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_801F86F4(s32 value);

s32 fn_80057E3C(void *context, void *event, s32 *result)
{
    char *strings = lbl_80243A40;
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);

    if (kind == 1) {
        s32 allowed = fn_80054BCC(lbl_8064D18C);

        fn_8011E174(8, 1);
        fn_801301B0(object, 0, 0x20);
        if (fn_800460EC() != 0) {
            fn_800073D8(lbl_8064D18C);
            lbl_8064B4F8 = 0;
        } else {
            fn_802020B4(context, 0);
            fn_80045A24(1, 0);
            lbl_8064B4F8 = 1;
        }
        if (allowed != 0) {
            void *resource = fn_801E741C(strings + 0x88);
            if (fn_80054D14(resource, context, object, 0) == 0) {
                fn_80054DF4(resource, context, object, 0);
                lbl_8064C86C = -1;
            }
        }
        return 1;
    }
    if (kind == 12) {
        fn_800C4F48(context, object, event, result);
        return 1;
    }
    if (kind == 22) {
        s32 sounds[8] = {
            0x2CB, 0x2CC, 0x2CD, 0x2CE,
            0x2CF, 0x2D0, 0x2D1, 0x2D1
        };
        s32 sound = sounds[rand() & 7];
        fn_801B05E8(sound, 100, 2, 1, 0, 5, 0, 0);
        return 1;
    }
    if (kind == 7) {
        if (fn_80035FB8(context, strings + 0xA0, &lbl_8064B4FC,
                        strings + 0xCC, &lbl_8064B4E4,
                        strings + 0xD8) == 0) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 2) {
        fn_8011E174(8, 0);
        fn_801301B0(object, 0x20, 0);
        if (lbl_8064C86C == -1) {
            fn_801F86F4(0);
        }
        if (lbl_8064B4F8 != 0) {
            fn_80045A24(0, 0);
            fn_802020B4(context, 1);
        }
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 135) return 1;
    if (kind == 40) return 1;
    if (kind == 32) return 1;
    if (kind == 46) return 1;
    if (kind == 41) return 1;
    if (kind == 42) return 1;
    if (kind == 43) return 1;
    if (kind == 147) return 1;
    if (kind == 175) return 1;
    return (u8)(kind == 31);
}
