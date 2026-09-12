typedef unsigned long long u64;
extern int lbl_8064D5C0;
extern u64 lbl_8064D5C8;
extern u64 lbl_8064D5D0;
extern u64 OSGetTime(void);

void fn_801E8D54(void)
{
    /* NonMatching: GC/1.3 schedules the 64-bit accumulator update
     * differently from retail despite preserving size and behavior. */
    if (lbl_8064D5C0 == 0) {
        u64 now = OSGetTime();
        lbl_8064D5C8 += now - lbl_8064D5D0;
        lbl_8064D5D0 = OSGetTime();
    }
}
