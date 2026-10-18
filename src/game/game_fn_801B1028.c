typedef unsigned char u8;

extern char __DTKVolumeL;
extern char __DTKVolumeR;
extern void* __DTKInterruptFrequency;
extern void AISetStreamVolLeft(int);
extern void AISetStreamVolRight(int);
extern void AIResetStreamSampleCount(void);
extern void AISetStreamTrigger(void*);
extern void AISetStreamPlayState(int);

#pragma optimization_level 1
void __DTKStartAi(void)
{
    AISetStreamVolLeft((u8)__DTKVolumeL);
    AISetStreamVolRight((u8)__DTKVolumeR);
    AIResetStreamSampleCount();
    AISetStreamTrigger(__DTKInterruptFrequency);
    AISetStreamPlayState(1);
}
#pragma optimization_level reset
