extern void fn_80229B08(int, int, int, int, int);
extern void fn_80229B88(int, int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_80229CCC(int, int, int, int, int, int);

void fn_80229964(int index, int mode) {
    int color = 10;
    int alpha = 5;

    if (index != 0) {
        color = 0;
        alpha = 0;
    }

    switch (mode) {
    case 0:
        fn_80229B08(index, 15, 8, color, 15);
        fn_80229B88(index, 7, 4, alpha, 7);
        break;
    case 1:
        fn_80229B08(index, color, 8, 9, 15);
        fn_80229B88(index, 7, 7, 7, alpha);
        break;
    case 2:
        fn_80229B08(index, color, 12, 8, 15);
        fn_80229B88(index, 7, 4, alpha, 7);
        break;
    case 3:
        fn_80229B08(index, 15, 15, 15, 8);
        fn_80229B88(index, 7, 7, 7, 4);
        break;
    case 4:
        fn_80229B08(index, 15, 15, 15, color);
        fn_80229B88(index, 7, 7, 7, alpha);
        break;
    }

    fn_80229C0C(index, 0, 0, 0, 1, 0);
    fn_80229CCC(index, 0, 0, 0, 1, 0);
}
