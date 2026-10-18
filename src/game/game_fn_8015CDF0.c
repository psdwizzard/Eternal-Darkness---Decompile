extern unsigned char lbl_805BB1E0[];
extern void VIWaitForRetrace(void);

void fn_8015CDF0(void)
{
    unsigned char* state = lbl_805BB1E0;

    while (state[2] >= 2 && state[3] == 3) {
        VIWaitForRetrace();
        VIWaitForRetrace();
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
}
