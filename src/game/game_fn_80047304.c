extern int lbl_8064C80C;
extern int lbl_8064C810;

extern int fn_801EBC1C(void);

int fn_80047304(void)
{
    int unavailable;

    if (lbl_8064C80C > 0) {
        unavailable = fn_801EBC1C() == 0;
        if (unavailable) {
            goto done;
        }
        if (lbl_8064C810 == 0) {
            lbl_8064C80C--;
        }
    } else {
        lbl_8064C80C = 0;
    }
done:
    return lbl_8064C80C;
}
