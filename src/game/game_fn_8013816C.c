extern int fn_800467E8(void);
extern void* memset(void*, int, unsigned int);
extern void* fn_8015E7A8(void);
extern void fn_80139298(void);
extern int fn_8020D318(void*, void*, int);
extern void fn_8020D1F0(void*, void*, int);

extern void* lbl_8064CFC0;
extern void* lbl_8064CFF8;
extern int lbl_8064CFFC;
extern int lbl_8064D000;
extern int lbl_8064D004;
extern unsigned int lbl_8064D010;
extern unsigned char lbl_805ADFE0[];
extern unsigned char lbl_805AE000[];
extern int lbl_8064CFC8;
extern int lbl_8064CFD0;

void fn_8013816C(void)
{
    int size = fn_800467E8() * 0x2F8LL;
    void* arena;

    arena = lbl_8064CFC0;
    lbl_8064CFF8 = arena;
    memset(arena, 0, size);
    lbl_8064D004 = 0;
    lbl_8064D000 = 0;
    lbl_8064CFFC = 0;
    lbl_8064D010 = (size + 0x1F) & ~0x1F;
    fn_8015E7A8();
    fn_80139298();
    fn_8020D318(lbl_805ADFE0, 0, 0);
    fn_8020D318(lbl_805AE000, 0, 0);
    fn_8020D1F0(lbl_805ADFE0, &lbl_8064CFC8, 2);
    fn_8020D1F0(lbl_805AE000, &lbl_8064CFD0, 2);
}
