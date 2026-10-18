typedef unsigned int u32;
typedef signed int s32;
typedef void (*DVDLowCallback)(u32 intType);

extern s32 DVDLowStopMotor(DVDLowCallback callback);
extern void cbForStateGoToRetry(u32 intType);

void stateGoToRetry(void)
{
    DVDLowStopMotor(cbForStateGoToRetry);
}
