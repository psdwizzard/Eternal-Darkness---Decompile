extern char lbl_80265AF8[];
extern void* lbl_8064D5B8;
extern void* fn_801FEA8C(unsigned int, unsigned int, const char*, unsigned int);
extern void* fn_8017CCD8(void*, unsigned int, unsigned int);
void fn_801E8A0C(void)
{
    void* memory = fn_801FEA8C(3600, 1, lbl_80265AF8, 24);
    lbl_8064D5B8 = fn_8017CCD8(memory, 36, 100);
}
