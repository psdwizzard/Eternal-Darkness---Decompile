extern void fn_8017BA24(int);
extern void DVDClose(void *);
extern void *lbl_8064CDE0;
extern void fn_8015DAB0(void *);
extern int lbl_8064CDAC;
extern unsigned char lbl_8024E394[];
extern unsigned char lbl_803322C0[];
extern void DVDOpen(void *, void *);
extern void *lbl_8064CD84;
extern void fn_8011824C(void *, void *);
extern int DVDReadAsyncPrio(void *, void *, unsigned int, int, void (*)(void *, void *), int);
extern void *fn_8015AA0C(void);
extern void fn_8015AA14(void);

void fn_80118288(int value, void *resource)
{
    fn_8017BA24(value);
    if (value >= 0) {
        if (resource != 0) {
            DVDClose(resource);
            fn_8015DAB0(lbl_8064CDE0);
        }
        lbl_8064CDAC = 1;
        DVDOpen(lbl_8024E394, lbl_803322C0);
        while (DVDReadAsyncPrio(lbl_803322C0, lbl_8064CD84,
                           (*(unsigned int *)(lbl_803322C0 + 0x34) + 0x1F) & ~0x1F,
                           0, fn_8011824C, 2) == 0) {
        }
        fn_8015AA0C();
        fn_8015AA14();
    }
}
