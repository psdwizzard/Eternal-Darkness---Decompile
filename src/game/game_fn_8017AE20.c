extern int lbl_8064D1F8;
extern unsigned char lbl_8064A580[];
extern const char lbl_80250EE0[];

extern void CARDInit(void);
extern void* fn_801FEA8C(int, int, const char*, int);
extern void fn_8017AE90(void);

void fn_8017AE20(int value)
{
    if (lbl_8064D1F8 == 0) {
        CARDInit();
        lbl_8064D1F8 = 1;
        *(int*)(lbl_8064A580 + 0xC) = value;
        *(void**)lbl_8064A580 = fn_801FEA8C(value, 1, lbl_80250EE0, 0x43);
        fn_8017AE90();
    }
}
