extern volatile unsigned int __DTKShutdownFlag;
extern int __DTKState;

extern void DTKFlushTracks(void*);
extern void AIRegisterStreamCallback(void*);
extern void AIResetStreamSampleCount(void);
extern void AISetStreamPlayState(int);
extern void AISetStreamVolLeft(int);
extern void AISetStreamVolRight(int);

void DTKShutdown(void)
{
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(0);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
    __DTKShutdownFlag = 1;
    DTKFlushTracks(0);
    __DTKState = 0;
    while (__DTKShutdownFlag != 0) {
    }
}
