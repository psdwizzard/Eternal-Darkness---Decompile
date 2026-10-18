extern unsigned int lbl_8064CC74;
extern void* lbl_8064CC78;
extern int DVDGetCommandBlockStatus(void*);

int fn_80108510(void)
{
    if (lbl_8064CC74 == 1) {
        return -1;
    }
    if (lbl_8064CC78 != 0) {
        return DVDGetCommandBlockStatus(lbl_8064CC78);
    }
    return 9;
}
