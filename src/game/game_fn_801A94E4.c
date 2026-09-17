typedef signed long s32;

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

extern Pair lbl_80650E48;
extern s32 lbl_8064D290;
extern s32 lbl_8064D294;
extern s32 lbl_8064D298;

extern void fn_8021A4C0(s32);
extern void fn_801CD404(Pair*);
extern void fn_801CA288(s32, s32, s32, s32, s32, s32);
extern void fn_801B1440(void);
extern void fn_801AAA28(void);
extern void fn_801A9C78(void);
extern void fn_801ACD08(void);
extern void fn_801A96A8(s32, s32, s32);
extern void fn_801ACD8C(void);
extern void fn_801AD404(s32, s32, s32);
extern void fn_801AD490(void);
extern void fn_801AC350(s32, s32, s32);
extern void fn_801AF000(s32);
extern void fn_801B8F50(void);
extern void fn_801AA6D0(s32, s32, s32, s32);
extern void fn_801A9A40(s32, s32, s32);
extern void fn_801B8F84(s32, s32, s32);
extern void fn_802364B8(s32);
extern void fn_801B19D8(void);

s32 fn_801A94E4(s32 arg0, s32 enabled, s32 next, s32 fade)
{
    s32 changed = 0;
    Pair pair = lbl_80650E48;

    if (lbl_8064D290 == 0) {
        fn_8021A4C0(0);
        fn_801CD404(&pair);
        fn_801CA288(32, 32, 32, 1, 1, 0x5FC000);
        fn_801B1440();
        fn_801AAA28();
        fn_801A9C78();
        fn_801ACD08();
        lbl_8064D298 = 0;
        fn_801A96A8(-1, 0, 1);
    } else if (enabled != 0) {
        fn_801ACD8C();
        fn_801AD404(0, 0, 5);
        fn_801AD490();
        fn_801AD404(100, 100, 1);
        fn_801AC350(10, 0, 0);
        fn_801AF000(lbl_8064D290);
        fn_801B8F50();
    }

    if (next != -1 && lbl_8064D298 != next) {
        changed = 1;
        if (enabled != 1) {
            s32 discriminator;
            changed = 1;
            discriminator = enabled == 1 ? 10 : 29;
            if (lbl_8064D298 == 0) {
                fn_801AA6D0(next, arg0, 0, discriminator);
            } else {
                fn_801AA6D0(next, arg0, lbl_8064D290, discriminator);
            }
            lbl_8064D298 = next;
        }
    }

    if (enabled != 0) {
        if (fade != 0) {
            fn_801A9A40(0, 127, 127);
            fn_801B8F84(127, 0, 255);
        }
        fn_801AF000(lbl_8064D290);
        fn_802364B8(lbl_8064D290);
        fn_801B19D8();
        fn_801A9C78();
        fn_801A96A8(lbl_8064D294, 0, 1);
        lbl_8064D290 = 1;
    }
    return changed;
}
