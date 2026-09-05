typedef unsigned short u16;
typedef unsigned int u32;

extern char lbl_80255780[];
extern void* lbl_8064D540;
extern void* lbl_8064D544;
extern void* lbl_8064D554;
extern void* fn_801FEA8C(u32, u32, const char*, u32);
extern void* fn_8017CCD8(void*, u32, u32);
extern void fn_801D1388(void);

void fn_801D1054(u32 count)
{
    void* allocation = fn_801FEA8C((u16)count * 0xFF8, 1, lbl_80255780, 663);
    lbl_8064D554 = fn_8017CCD8(allocation, 0xFF8, count);
    lbl_8064D544 = 0;
    lbl_8064D540 = 0;
    fn_801D1388();
}
