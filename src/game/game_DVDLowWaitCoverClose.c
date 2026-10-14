typedef signed int s32;
typedef unsigned int u32;
typedef void (*DVDLowCallback)(u32 intType);

extern DVDLowCallback Callback_8064D9A0;
extern volatile s32 WaitingCoverClose_8064D9B4;
extern volatile s32 StopAtNextInt_8064D998;

volatile u32 __DIRegs[16] : 0xCC006000;

s32 DVDLowWaitCoverClose(DVDLowCallback callback)
{
    Callback_8064D9A0 = callback;
    WaitingCoverClose_8064D9B4 = 1;
    StopAtNextInt_8064D998 = 0;
    __DIRegs[1] = 2;
    return 1;
}
