typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;

extern char lbl_80243AC8[];
extern s32 lbl_8064B4E0;
extern s32 lbl_8064C86C;
extern s32 lbl_8064D18C;

extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void fn_8011E174(s32 index, s32 value);
extern int fn_801301B0(void *object, s32 set, s32 clear);
extern void fn_801B05E8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 fn_800460EC(void);
extern void fn_800073D8(s32 value);
extern void fn_802020B4(void *object, s32 value);
extern void fn_80045A24(s32 value, s32 mode);
extern s32 fn_80054BCC(s32 value);
extern void *fn_801E741C(char *name);
extern s32 fn_80054D14(void *context, void *owner, void *object, s32 force);
extern void fn_80054DF4(void *context, void *owner, void *object, s32 force);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8012B344(void*);
extern void fn_800C63D8(void);
extern void *fn_801294DC(void *, int, int, int);
extern s32 fn_80128EAC(void *object);
extern unsigned long long fn_8020123C();
extern void fn_80128C28();
extern void fn_80204810(void);
extern int fn_80038308(void *, int, short *);
extern int fn_80038464(void *object, s32 index, s16 *value);
extern int fn_800389E0(void *object, s32 index, s16 value, s32 mode);
extern void fn_801F86F4(s32 value);

s32 fn_80055350(void *context, void *event, s32 *result)
{
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);
    void *owner = (void *)fn_80201B54(context);
    u8 *state = fn_80201B8C(context);

    if (kind == 1) {
        s32 allowed = fn_80054BCC(lbl_8064D18C);

        fn_8011E174(8, 1);
        fn_801301B0(object, 0, 0x20);
        fn_801B05E8(0x154, 100, 2, 1, 0, 5, 0, 0);
        if (fn_800460EC() != 0) {
            fn_800073D8(lbl_8064D18C);
            lbl_8064B4E0 = 0;
        } else {
            fn_802020B4(context, 0);
            fn_80045A24(1, 0);
            lbl_8064B4E0 = 1;
        }
        if (allowed != 0) {
            void *resource = fn_801E741C(lbl_80243AC8);
            if (fn_80054D14(resource, context, object, 0) == 0) {
                lbl_8064C86C = -1;
                fn_80054DF4(resource, context, object, 0);
            }
        }
        return 1;
    }
    if (kind == 61) {
        fn_80201D2C(context, 1);
        fn_80201D14(context, 1);
        fn_8012B344(object);
        fn_800C63D8();
        return 1;
    }
    if (kind == 171) {
        if (fn_801294DC(object, 0x90, 0x25, 8) == 0) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 44) {
        if (fn_80128EAC(object) != 0x91 && fn_80128EAC(object) != 0x8F) {
            fn_8020123C(5, owner, owner, 0);
        }
        return 1;
    }
    if (kind == 5) {
        void *entry = fn_801294DC(object, 0x91, 0x24, 8);
        if (entry != 0) {
            fn_80128C28(entry, fn_80204810, ((s32)owner << 8) | 6);
        } else {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 6) {
        fn_80201D2C(context, 1);
        fn_80201D14(context, 1);
        return 1;
    }
    if (kind == 135) {
        fn_80201D2C(context, 1);
        fn_80201D14(context, 1);
        fn_8012B344(object);
        if (result != 0) {
            *result = 1;
        }
        fn_800C63D8();
        fn_8020123C(135, owner, *(void **)((u8 *)*(void **)state + 0x70), 0);
        return 1;
    }
    if (kind == 2) {
        s16 first;
        s16 second;

        fn_8011E174(8, 0);
        fn_801301B0(object, 0x20, 0);
        fn_80038308(context, 1, &first);
        fn_80038464(context, 1, &second);
        fn_800389E0(context, 1, (s16)(first + 255), 1);
        if (lbl_8064C86C == -1) {
            fn_801F86F4(0);
        }
        if (lbl_8064B4E0 != 0) {
            fn_80045A24(0, 0);
            fn_802020B4(context, 1);
        }
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 46) return 1;
    if (kind == 41) return 1;
    if (kind == 42) return 1;
    if (kind == 43) return 1;
    if (kind == 147) return 1;
    if (kind == 135) return 1;
    if (kind == 175) return 1;
    if (kind == 202) return 1;
    return (u8)(kind == 31);
}
