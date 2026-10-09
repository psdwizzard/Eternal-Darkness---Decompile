extern unsigned int fn_801380EC(void);
extern void fn_8020D1F0(void*, void*, int);

extern void* lbl_8064CFC0;
extern int lbl_8064CFC8;
extern int lbl_8064CFD0;
extern int lbl_8064D00C;
extern unsigned char lbl_805ADFE0[];
extern unsigned char lbl_805AE000[];

void* fn_801380F8(void* base)
{
    unsigned int size;

    size = fn_801380EC();
    lbl_8064CFC0 = base;
    base = (unsigned char*)base + size;
    lbl_8064D00C = 0;
    fn_8020D1F0(lbl_805ADFE0, &lbl_8064CFC8, 2);
    fn_8020D1F0(lbl_805AE000, &lbl_8064CFD0, 2);
    return base;
}
