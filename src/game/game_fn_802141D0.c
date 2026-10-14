typedef unsigned int u32;
typedef signed int s32;
typedef void (*DVDLowCallback)(u32 intType);

extern s32 DVDLowStopMotor(DVDLowCallback callback);
extern void fn_802141F8(u32 intType);

void fn_802141D0(void)
{
    DVDLowStopMotor(fn_802141F8);
}
