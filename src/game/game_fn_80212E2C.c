typedef signed int s32;
typedef unsigned int u32;
typedef signed long long OSTime;
typedef void (*DVDLowCallback)(u32 intType);

typedef struct OSAlarm {
    char data[0x28];
} OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm *alarm, void *context);

extern DVDLowCallback Callback_8064D9A0;
extern volatile s32 StopAtNextInt_8064D998;
extern OSAlarm AlarmForTimeout_806418E8;
extern void OSCreateAlarm(OSAlarm *alarm);
extern void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);
extern void AlarmHandlerForTimeout_80212558(OSAlarm *alarm, void *context);

volatile u32 __DIRegs[16] : 0xCC006000;

static inline void SetTimeoutAlarm(OSTime timeout) {
    OSCreateAlarm(&AlarmForTimeout_806418E8);
    OSSetAlarm(&AlarmForTimeout_806418E8, timeout, AlarmHandlerForTimeout_80212558);
}

/* Configure the disc audio buffer and start the command timeout. */
s32 DVDLowAudioBufferConfig(s32 enable, u32 size, DVDLowCallback callback) {
    u32 enableBit;

    Callback_8064D9A0 = callback;
    StopAtNextInt_8064D998 = 0;
    enableBit = enable ? 0x10000 : 0;
    __DIRegs[2] = size | (enableBit | 0xE4000000);
    __DIRegs[7] = 1;
    SetTimeoutAlarm((*(u32 *)0x800000F8 / 4) * 10);
    return 1;
}
