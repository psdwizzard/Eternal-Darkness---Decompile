extern unsigned int lbl_8064CD48;
extern unsigned int lbl_8064CD4C;

int fn_80113BC0(unsigned int flags)
{
    int i;
    unsigned int bit;

    for (i = 0; i < 14; i++) {
        bit = 1U << i;
        if ((flags & bit) && !(lbl_8064CD4C & bit)) {
            return 0;
        }
    }
    /* The retail code retains this empty-range check of the upper flags. */
    for (i = 16; i < 16; i++) {
        bit = 1U << i;
        if ((flags & bit) && !(lbl_8064CD48 & bit)) {
            return 0;
        }
    }
    return 1;
}
