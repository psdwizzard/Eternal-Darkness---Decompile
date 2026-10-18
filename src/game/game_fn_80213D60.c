typedef unsigned int u32;
typedef int s32;
typedef void (*DVDLowCallback)(u32 intType);

extern s32 DVDLowRequestError(DVDLowCallback callback);
extern void cbForStateGettingError(u32 error);

void stateGettingError(void) {
    DVDLowRequestError(cbForStateGettingError);
}
