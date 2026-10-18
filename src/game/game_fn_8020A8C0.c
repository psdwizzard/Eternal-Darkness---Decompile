typedef int BOOL;
typedef unsigned int u32;
typedef signed long long OSTime;
typedef unsigned long long u64;

typedef struct OSContext OSContext;
typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm* prev;
    OSAlarm* next;
    OSTime period;
    OSTime start;
};

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u64 __OSTimeToSystemTime(u64 time);
extern void InsertAlarm_8020A608(OSAlarm* alarm, OSTime fire, OSAlarmHandler handler);

/* OSSetPeriodicAlarm */
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    alarm->period = period;
    alarm->start = __OSTimeToSystemTime(start);
    InsertAlarm_8020A608(alarm, 0, handler);
    OSRestoreInterrupts(enabled);
}
