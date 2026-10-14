typedef unsigned int u32;
typedef int s32;
typedef void (*DVDLowCallback)(u32 intType);

extern s32 DVDLowWaitCoverClose(DVDLowCallback callback);
extern void cbForStateMotorStopped_8021492C(u32 intType);

void fn_80214904(void)
{
    DVDLowWaitCoverClose(cbForStateMotorStopped_8021492C);
}
