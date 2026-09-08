typedef unsigned long long u64;
extern unsigned int lbl_8064D5C8;
extern unsigned int lbl_8064D5CC;
extern void fn_801E8D54(void);

u64 fn_801E8E2C(void)
{
    fn_801E8D54();
    return ((u64)lbl_8064D5C8 << 32) | lbl_8064D5CC;
}
