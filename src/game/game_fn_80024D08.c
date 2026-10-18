extern void PPCMtmmcr0(int);
extern void PPCMtmmcr1(int);
extern void PPCMfpmc1(void);
extern void srand(void);

void fn_80024D08(void)
{
    PPCMtmmcr0(0);
    PPCMtmmcr1(0);
    PPCMfpmc1();
    srand();
}
