extern int fn_80201AE4();
extern int fn_80201B44();
extern int lbl_8064C5C4;
extern int lbl_8064C5C8;

void fn_80046C98(int arg0) {
    int cur = fn_80201B44();
    int want = fn_80201AE4();
    lbl_8064C5C4 = arg0;
    if (cur == want) {
        lbl_8064C5C8 = arg0;
    }
}
