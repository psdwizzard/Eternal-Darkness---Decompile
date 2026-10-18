typedef unsigned char u8;

extern void* __DTKCurrentTrack;
extern void* __DTKPlayListHead;
extern void* __DTKPlayListTail;
extern int __DTKState;
extern int __DTKRepeatMode;
extern int __DTKPosition;
extern int __DTKInterruptFrequency;
extern u8 __DTKVolumeL;
extern u8 __DTKVolumeR;

extern void __DTKCallbackForAIInterrupt(void);
extern void AIRegisterStreamCallback(void (*)(void));
extern void AIResetStreamSampleCount(void);
extern void AISetStreamPlayState(int);
extern void AISetStreamVolLeft(int);
extern void AISetStreamVolRight(int);

void DTKInit(void)
{
    __DTKCurrentTrack = 0;
    __DTKPlayListHead = 0;
    __DTKPlayListTail = 0;
    __DTKState = 0;
    __DTKRepeatMode = 0;
    __DTKPosition = 0;
    __DTKInterruptFrequency = 48000;
    __DTKVolumeL = 255;
    __DTKVolumeR = 255;
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(__DTKCallbackForAIInterrupt);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
}
