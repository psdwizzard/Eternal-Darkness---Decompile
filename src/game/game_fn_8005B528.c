typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;

#pragma use_lmw_stmw on

typedef struct GameState {
    s32 value;
    s32 previous;
    s32 mode;
} GameState;

extern GameState lbl_803003C8;
extern s32 *lbl_8064C5A8;
extern u32 lbl_80651948;
extern u32 lbl_8065194C;
extern u32 lbl_8064E550;
extern float lbl_8064E504;
extern float lbl_8064E554;
extern float lbl_8064E558;

extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern void fn_8001D9FC(s32 value);
extern void fn_801EFE84(s32 value);
extern void fn_80130434(void *object, s32 value);
extern void fn_801301B0(void *object, s32 set, s32 clear);
extern void fn_8011E1C4(void);
extern void fn_8011E174(s32 value, s32 enabled);
extern u32 fn_8015C910(void);
extern void fn_80128754(void *object, s32 value);
extern s32 fn_800A1060(void);
extern s32 fn_802006D4(s32 source, s32 target, s32 value, s32 kind, s32 flags);
extern void fn_801AD404(s32 first, s32 second, s32 third);
extern void fn_801AD734(s32 value);
extern void fn_8011FABC(void *object, s32 set, s32 clear);
extern void fn_801ACD8C(void);
extern s32 fn_80128EAC(void *object);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8012B344(void*);
extern void fn_800C2708(s32 value, s32 object_id);
extern int fn_80038464(void *context, s32 index, s16 *value);
extern int fn_800389E0(void *context, s32 index, s32 value, s32 enabled);
extern void fn_80120AD0(void *object, s32 value, s32 amount, s32 flags,
                       float first, float second);
extern void fn_801B05E8(s32, s32, s32, s32, s32, s32, s32, s32);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a, b, c, d, e) fn_8020104C((a), (void *)(b), (void *)(c), (int)(d), (e))
extern void fn_801F348C(u32 *value, s32 frames);
extern s32 fn_800AD3E4(void);
extern void fn_80052424(s32 value, s32 next, s32 third, s32 fourth);
extern void fn_80045A24(s32 value, s32 mode);
extern void fn_80025A78(s32 value);

s32 fn_8005B528(void *context, void *event, u32 *result)
{
    s32 kind = fn_80200C10(event);
    void *object = fn_80201BC8(context);
    s32 object_type = fn_8011EB04(object);
    s32 object_id = fn_80201B54(context);

    if (kind == 1) {
        fn_8001D9FC(2);
        fn_801EFE84(0);
        fn_80130434(object, 1);
        fn_801301B0(object, 0, 0x20);
        fn_8011E1C4();
        fn_8011E174(0x40, 1);
        fn_8015C910();
        fn_80128754(object, -1);
        if (fn_800A1060() != 0) {
            fn_802006D4(object_id, object_id, 8, 0x11, 0);
            fn_801AD404(50, 50, 5);
            fn_801AD734(60);
            fn_801AD404(100, 100, 30);
            fn_8011FABC(object, 0, 0x8000);
        } else if (object_type != 0x55 && object_type != 0x77 &&
                   object_type != 0x78 && object_type != 0x79 &&
                   object_type != 0x7A) {
            fn_801ACD8C();
            fn_801AD404(50, 50, 5);
            fn_801AD734(600);
            fn_801AD404(100, 100, 30);
            fn_8011FABC(object, 0, 0x8000);
        }
        return 1;
    }
    if (kind == 3) {
        fn_80128EAC(object);
        return 1;
    }
    if (kind == 0xE5) {
        if (fn_800A1060() != 0) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            fn_8012B344(object);
        }
        return 1;
    }
    if (kind == 0x3D) {
        fn_800A1060();
        return 1;
    }
    if (kind == 7) {
        fn_800A1060();
        return 1;
    }
    if (kind == 6) {
        s16 value;
        if (fn_800A1060() != 0) {
            fn_800C2708(0, object_id);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
        } else {
            if (object_type == 0x55) goto special_type;
            if (object_type == 0x77) goto special_type;
            if (object_type == 0x78) goto special_type;
            if (object_type == 0x79) goto special_type;
            if (object_type == 0x7A) goto special_type;
            goto ordinary_type;
special_type:
            value = 100;
            fn_80038464(context, 0, &value);
            fn_800389E0(context, 0, value, 1);
            fn_80120AD0(object, 0, 100, 0x102, lbl_8064E504,
                        lbl_8064E554);
            fn_801B05E8(0x21D, 100, 3, 1, 0, 5, 0, 0);
            fn_801294DC(object, 0x29, 0x20, 10);
            fn_8011FABC(object, 0x8000, 0);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            goto kind_6_done;
ordinary_type:
        {
            u32 value[2];
            fn_8020104C(0x11, object_id, object_id, 0, lbl_8064E558);
            value[0] = lbl_8064E550;
            value[1] = lbl_8064E550;
            fn_801F348C(&value[1], 120);
        }
kind_6_done:
            ;
        }
        return 1;
    }
    if (kind == 0x11) {
        if (lbl_803003C8.mode == 13 && fn_800AD3E4() != 8) {
            u32 timer[2];
            s32 values[3] = {0x5B, 0x61, 0x62};
            s32 value = values[*lbl_8064C5A8 - 1];
            timer[0] = lbl_80651948;
            timer[1] = lbl_80651948;
            fn_801F348C(&timer[1], 1);
            fn_80052424(value, -1, 0, 0);
        } else {
            u32 timer[2];
            timer[0] = lbl_8065194C;
            timer[1] = lbl_8065194C;
            fn_801F348C(&timer[1], 120);
            fn_80045A24(0, 0);
            fn_80025A78(3);
        }
        return 1;
    }
    if (kind == 2) {
        fn_8011E174(0x40, 0);
        fn_80128754(object, -2);
        fn_801301B0(object, 0x20, 0);
        fn_802006D4(object_id, object_id, 8, 0x11, 0);
        fn_8011FABC(object, 0x8000, 0);
        return 1;
    }
    if (kind == 0x34) return 1;
    if (kind == 0x85) return 1;
    if (kind == 0x74) return 1;
    if (kind == 0x20) return 1;
    if (kind == 0x6B) return 1;
    if (kind == 0x3B) return 1;
    if (kind == 0x99) return 1;
    if (kind == 0x87) return 1;
    if (kind == 0x0B) return 1;
    if (kind == 0x1E) return 1;
    if (kind == 0x08) return 1;
    if (kind == 0x29) return 1;
    if (kind == 0x2A) return 1;
    if (kind == 0x2B) return 1;
    if (kind == 0x2D) return 1;
    if (kind == 0x2C) return 1;
    if (kind == 0x28) return 1;
    if (kind == 0x27) return 1;
    if (kind == 0x7D) return 1;
    if (kind == 0xAF) return 1;
    if (kind == 0xB9) return 1;
    if (kind == 0x67) return 1;
    if (kind == 0xF2) return 1;
    if (kind == 0xC5) return 1;
    if (kind == 0xCF) return 1;
    if (kind == 0xD0) return 1;
    if (kind == 0xB1) return 1;
    if (kind == 0xC6) return 1;
    if (kind == 0x9B) return 1;
    if (kind == 0xCA) return 1;
    if (kind == 0x93) return 1;
    if (kind == 0x1F) return 1;
    if (kind != 0x86) goto rejected;
    return 1;
rejected:
    return 0;
}
