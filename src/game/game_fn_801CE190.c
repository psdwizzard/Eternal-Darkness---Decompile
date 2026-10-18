typedef unsigned short u16;
typedef unsigned int u32;

extern u16 dspCmdFirstSize;
extern u32 dspCmdList;
extern u32 salDspIsDone;

extern u32 salGetStartDelay(void);
extern void salBuildCommandList(void*, u32);
extern void PPCSync(void);
extern void DSPSendMailToDSP(u32);
extern u32 DSPCheckMailToDSP(void);

void salCtrlDsp(void* argument)
{
    u32 saved;

    salBuildCommandList(argument, salGetStartDelay());
    salDspIsDone = 0;
    saved = dspCmdList;
    PPCSync();
    DSPSendMailToDSP((u32)dspCmdFirstSize | 0xBABE0000);
    while (DSPCheckMailToDSP() != 0) {
    }
    DSPSendMailToDSP(saved);
    while (DSPCheckMailToDSP() != 0) {
    }
}
