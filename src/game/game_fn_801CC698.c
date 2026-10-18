extern void hwDisableIrq(void);
extern void salExitDsp(void);
extern void salExitDspCtrl(void);
extern void salExitAi(void);
extern void hwEnableIrq(void);
extern void hwExitIrq(void);

void hwExit(void)
{
    hwDisableIrq();
    salExitDsp();
    salExitDspCtrl();
    salExitAi();
    hwEnableIrq();
    hwExitIrq();
}
