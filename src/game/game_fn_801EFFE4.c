extern int lbl_8064D760;

extern void fn_8022551C(int, int, int, int, int);

void fn_801EFFE4(int value)
{
    if (lbl_8064D760 != value) {
        lbl_8064D760 = value;
        fn_8022551C(1, 9, 1, 3, value & 0xFF);
        fn_8022551C(7, 9, 1, 3, lbl_8064D760 & 0xFF);
    }
}
