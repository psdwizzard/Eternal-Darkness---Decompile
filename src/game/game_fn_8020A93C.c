typedef int BOOL;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef s64 OSTime;

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

typedef struct OSAlarmQueue {
    OSAlarm* head;
    OSAlarm* tail;
} OSAlarmQueue;

extern OSAlarmQueue AlarmQueue_8064D918;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
/* Defined in src/dolphin/os/OSGetSystemTime.c with an unsigned 64-bit return. */
extern u64 __OSGetSystemTime(void);
extern void PPCMtdec(u32 newDec);

static inline void SetTimer(OSAlarm* alarm)
{
    OSTime delta;

    delta = alarm->fire - (OSTime)__OSGetSystemTime();
    if (delta < 0) {
        PPCMtdec(0);
    } else if (delta < 0x80000000) {
        PPCMtdec((u32)delta);
    } else {
        PPCMtdec(0x7FFFFFFF);
    }
}

/* OSCancelAlarm */
void OSCancelAlarm(OSAlarm* alarm)
{
    OSAlarm* next;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (alarm->handler == 0) {
        OSRestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        AlarmQueue_8064D918.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }

    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        AlarmQueue_8064D918.head = next;
        if (next) {
            SetTimer(next);
        }
    }

    alarm->handler = 0;
    OSRestoreInterrupts(enabled);
}
