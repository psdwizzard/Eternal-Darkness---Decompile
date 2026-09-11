extern char lbl_802FC8E0[];
extern void *lbl_8064D86C;
extern void *lbl_8064D87C;

extern void *fn_801FEA8C(unsigned int, int, const char *, int);
extern void *fn_8017CCD8(void *, unsigned int, unsigned int);
extern void *fn_8017CDB4(void *);

void fn_802012A0(int mode)
{
    if (mode == 0) {
        void *storage = fn_801FEA8C(0x1130, 1, lbl_802FC8E0, 0x587);
        lbl_8064D87C = fn_8017CCD8(storage, 0x2C, 100);
    }
    lbl_8064D86C = fn_8017CDB4(lbl_8064D87C);
}
