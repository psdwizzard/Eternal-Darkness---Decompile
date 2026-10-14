typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed long long OSTime;
typedef int BOOL;

typedef struct OSContext OSContext;
typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm *alarm, OSContext *context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTime period;
    OSTime start;
};

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern u64 __OSGetSystemTime(void);
extern void InsertAlarm_8020A608(OSAlarm *alarm, OSTime fire, OSAlarmHandler handler);

void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    alarm->period = 0;
    InsertAlarm_8020A608(alarm, (OSTime)__OSGetSystemTime() + tick, handler);
    OSRestoreInterrupts(enabled);
}
