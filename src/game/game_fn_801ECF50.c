typedef unsigned int u32;

extern u32 lbl_8064D678;
extern void fn_80225FD8(void);
extern void fn_802254D0(void);
extern void fn_80224A60(int, int);

void fn_801ECF50(u32 mode)
{
    if (mode == lbl_8064D678) {
        return;
    }

    lbl_8064D678 = mode;
    fn_80225FD8();
    fn_802254D0();

    switch (mode) {
    case 1:
        fn_80224A60(9, 3);
        fn_80224A60(25, 3);
        fn_80224A60(13, 3);
        break;
    case 0:
        fn_80224A60(9, 3);
        fn_80224A60(25, 3);
        fn_80224A60(13, 3);
        fn_80224A60(14, 3);
        break;
    case 7:
        fn_80224A60(9, 3);
        fn_80224A60(10, 3);
        fn_80224A60(13, 3);
        break;
    case 2:
        fn_80224A60(9, 3);
        fn_80224A60(10, 3);
        fn_80224A60(13, 3);
        fn_80224A60(14, 3);
        break;
    case 3:
        fn_80224A60(9, 3);
        fn_80224A60(13, 3);
        fn_80224A60(11, 3);
        break;
    case 4:
        fn_80224A60(9, 1);
        break;
    case 6:
        fn_80224A60(9, 1);
        fn_80224A60(13, 3);
        break;
    case 5:
        fn_80224A60(9, 3);
        fn_80224A60(13, 3);
        break;
    case 8:
        fn_80224A60(9, 1);
        fn_80224A60(13, 1);
        break;
    case 9:
        fn_80224A60(9, 1);
        fn_80224A60(13, 1);
        fn_80224A60(11, 1);
        break;
    }
}
