typedef unsigned int u32;

extern void fn_8021B9E0(void);
extern u32 fn_8021BA20(void);
extern void fn_8021B998(void);

u32 fn_801CE15C(void)
{
    fn_8021B9E0();
    while (fn_8021BA20() != 0) {
    }
    fn_8021B998();
    return 1;
}
