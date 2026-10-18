typedef unsigned int u32;

extern void DSPHalt(void);
extern u32 DSPGetDMAStatus(void);
extern void DSPReset(void);

u32 salExitDsp(void)
{
    DSPHalt();
    while (DSPGetDMAStatus() != 0) {
    }
    DSPReset();
    return 1;
}
