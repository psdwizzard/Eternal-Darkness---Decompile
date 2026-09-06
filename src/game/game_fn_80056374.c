typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;

#pragma use_lmw_stmw on

extern char lbl_80243A40[];
extern char lbl_8064B4E4;
extern unsigned char lbl_8064C860;

extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern void fn_8011E174(s32 index, s32 value);
extern s32 fn_8004918C(void);
extern void *fn_80049194(void);
extern int fn_80201B44();
extern unsigned long long fn_8020123C();
extern void *fn_801A7778(s32 object);
extern int fn_801301B0(void *object, s32 set, s32 clear);
extern s32 fn_80035FB8(void *context, char *first, char *second, char *third,
                      char *value, char *fourth);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8012B344(void*);
extern u64 fn_802011D4(void *event);
extern u32 fn_801A6D9C(void *object);
extern void fn_8007C90C(void *context, void *event);
extern void fn_8007CAC4(void *context, void *event);

s32 fn_80056374(void *context, void *event, u32 *result)
{
    char *strings = lbl_80243A40;
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);

    if (kind == 1) {
        fn_8011E174(0x200, 1);
        return 1;
    }
    if (kind == 6) {
        fn_8004918C();
        fn_8020123C(0xB2, fn_80201B44(), fn_80201B44(), 0);
        return 1;
    }
    if (kind == 7) {
        fn_801A7778(fn_8004918C());
        fn_801301B0(object, 0x20, 0);
        if (fn_80035FB8(context, strings + 0xA0, strings + 0xF0,
                        strings + 0xCC, &lbl_8064B4E4, strings + 0xD8) == 0) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 41) {
        fn_8012B344(object);
        return 1;
    }
    if (kind == 42) {
        fn_8012B344(object);
        return 1;
    }
    if (kind == 44) {
        fn_8012B344(object);
        return 1;
    }
    if (kind == 43) {
        fn_8012B344(object);
        return 1;
    }
    if (kind == 40) {
        fn_8012B344(object);
        if (result != 0) {
            *result = fn_802011D4(event) & 0xFFFFFFFF;
        }
        return 1;
    }
    if (kind == 179) {
        if ((fn_801A6D9C(fn_80049194()) & 0x2000) != 0 || lbl_8064C860 != 0) {
            fn_8007C90C(context, event);
        } else {
            fn_8007CAC4(context, event);
        }
        return 1;
    }
    if (kind == 178) {
        fn_8007CAC4(context, event);
        return 1;
    }
    if (kind == 2) {
        fn_8011E174(0x200, 0);
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 135) return 1;
    if (kind == 30) return 1;
    if (kind == 105) return 1;
    if (kind == 125) return 1;
    if (kind == 147) return 1;
    if (kind == 177) return 1;
    if (kind == 155) return 1;
    if (kind == 204) return 1;
    if (kind == 46) return 1;
    return (u8)(kind == 31);
}
