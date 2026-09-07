extern int fn_80070E30(void);
extern int fn_800AE88C(unsigned int);
extern int fn_801AF824(int);
extern void fn_801B05B0(int, int);

void fn_800AF230(void)
{
    if (fn_80070E30() == 0) {
        int ids[4] = { 0, 1, 2, 4 };
        int i;
        int handle;

        for (i = 0; i < 4; i++) {
            handle = fn_800AE88C(ids[i]);
            if (fn_801AF824(handle) != 0) {
                fn_801B05B0(handle, 60);
            }
        }
    }
}
