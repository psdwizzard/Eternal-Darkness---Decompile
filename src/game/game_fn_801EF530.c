extern unsigned char lbl_8064C368;

extern void fn_80226378(void);
extern void* fn_80224640(void);
extern void fn_80224298(void*, void**, void**);
extern void fn_80224338(void*);
extern void fn_802264D4(unsigned long);

void fn_801EF530(void)
{
    void* first;
    void* second;

    fn_80226378();
    fn_80224298(fn_80224640(), &first, &second);
    fn_80224338(second);
    if (lbl_8064C368 != 0) {
        fn_802264D4(0xCACE);
    }
}
