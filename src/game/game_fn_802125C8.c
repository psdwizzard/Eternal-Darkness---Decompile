typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef s64 OSTime;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDCommand {
    s32 cmd;
    void *addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

typedef struct OSAlarm {
    char data[0x28];
} OSAlarm;

/* dvdlow.c static work area */
typedef struct DVDLowWork {
    DVDCommand cmdList[5];
    char pad_64[0x4];
    OSAlarm alarmForTimeout;
} DVDLowWork;

typedef void (*OSAlarmHandler)(OSAlarm *alarm, void *context);

extern DVDLowWork CommandList_80641880;
extern volatile s32 StopAtNextInt_8064D998;
extern DVDLowCallback Callback_8064D9A0;
extern volatile s32 LastCommandWasRead; /* LastCommandWasRead */
/* LastReadIssued; symbols.txt splits it into two 4-byte labels (D0/D4) */
extern OSTime LastReadIssued;
extern volatile u32 LastLength; /* LastLength */

extern OSTime __OSGetSystemTime(void);
extern void OSCreateAlarm(OSAlarm *alarm);
extern void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);
extern void AlarmHandlerForTimeout_80212558(OSAlarm *alarm, void *context);

volatile u32 __DIRegs[16] : 0xCC006000;

#define OS_BUS_CLOCK (*(u32 *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)

static inline void SetTimeoutAlarm(DVDLowWork *w, OSTime timeout) {
    OSCreateAlarm(&w->alarmForTimeout);
    OSSetAlarm(&w->alarmForTimeout, timeout, AlarmHandlerForTimeout_80212558);
}

/* dvdlow.c Read */
void Read(void *addr, u32 length, u32 offset, DVDLowCallback callback) {
    DVDLowWork *w = &CommandList_80641880;

    StopAtNextInt_8064D998 = FALSE;
    Callback_8064D9A0 = callback;
    LastCommandWasRead = TRUE;
    LastReadIssued = __OSGetSystemTime();

    __DIRegs[2] = 0xA8000000;
    __DIRegs[3] = offset >> 2;
    __DIRegs[4] = length;
    __DIRegs[5] = (u32)addr;
    __DIRegs[6] = length;
    LastLength = length;
    __DIRegs[7] = 3;

    if (length > 0xA00000) {
        SetTimeoutAlarm(w, OSSecondsToTicks(20));
    } else {
        SetTimeoutAlarm(w, OSSecondsToTicks(10));
    }
}
