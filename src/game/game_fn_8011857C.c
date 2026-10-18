extern unsigned int lbl_8064CDAC;
extern unsigned int lbl_8064CDA8;
extern unsigned int lbl_8064CDA4;
extern unsigned int lbl_8064CDA0;
extern unsigned int lbl_8064CDE0;
extern unsigned int lbl_8064CD80;
extern unsigned int lbl_8064CDE4;
extern unsigned int lbl_8064C51C;
extern unsigned int lbl_8064C5CC;
extern unsigned int lbl_8064CD7C;
extern unsigned int lbl_8064CD78;
extern unsigned int lbl_8064CD90;
extern unsigned int lbl_8064CD74;
extern unsigned char lbl_8024E3B4[];
extern unsigned char lbl_80332358[];

extern void fn_80118528(void);
extern int fn_801391AC(void);
extern void DVDOpen(void *, void *);
extern int DVDReadAsyncPrio(void *, void *, unsigned int, int, void *, int);
extern void DCInvalidateRange(void *, unsigned int);
extern void fn_8015E9EC(unsigned int, void *, unsigned int);
extern void fn_80118370(int, int);

void fn_8011857C(void)
{
    lbl_8064CDAC = 0;
    lbl_8064CDA8 = 0;
    lbl_8064CDA4 = 0;
    lbl_8064CDA0 = 0;
    lbl_8064CDE0 = 0;
    lbl_8064CD80 = 0;
    lbl_8064CDE4 = 0;
    lbl_8064C51C = 0;
    lbl_8064C5CC = 0;
    fn_80118528();
    lbl_8064CD90 = lbl_8064CD7C + lbl_8064CD78;

    if (fn_801391AC() != 0) {
        DVDOpen(lbl_8024E3B4, lbl_80332358);
        while (DVDReadAsyncPrio(lbl_80332358, (void *)lbl_8064CD90,
                           (*(unsigned int *)(lbl_80332358 + 0x34) + 31) & ~31,
                           0, fn_80118370, 2) == 0) {
        }
    } else {
        DCInvalidateRange((void *)lbl_8064CD90, lbl_8064CD74);
        fn_8015E9EC(0xEA5E40, (void *)lbl_8064CD90, lbl_8064CD74);
        fn_80118370(0, 0);
    }
}
