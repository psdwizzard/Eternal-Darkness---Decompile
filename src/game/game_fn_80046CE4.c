extern int fn_80201B44();
extern int fn_80201AE4();
extern void fn_80046D38(int);
extern int lbl_8064C804;

void fn_80046CE4(int arg) {
    int a = fn_80201B44();
    int b = fn_80201AE4();
    lbl_8064C804 = arg + 1;
    if (a == b) {
        fn_80046D38(arg);
    }
}
