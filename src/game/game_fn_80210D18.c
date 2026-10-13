typedef unsigned int u32;
typedef signed long long s64;
typedef s64 OSTime;

/* OSTicksToCalendarTime (Dolphin SDK OS/OSTime.c) */

typedef struct OSCalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
} OSCalendarTime;

u32 __OSBusClock : 0x800000F8;
#define OS_BUS_CLOCK __OSBusClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))
#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)

#define SECS_IN_DAY 86400
#define BIAS (2000 * 365 + (2000 + 3) / 4 - (2000 - 1) / 100 + (2000 - 1) / 400)

void fn_80210B7C(int days, OSCalendarTime *td);

void fn_80210D18(OSTime ticks, OSCalendarTime *td) {
    int days;
    int secs;
    OSTime d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0) {
        d += OSSecondsToTicks(1);
    }
    td->usec = (int)(OSTicksToMicroseconds(d) % 1000);
    td->msec = (int)(OSTicksToMilliseconds(d) % 1000);

    ticks -= d;
    days = (int)(OSTicksToSeconds(ticks) / SECS_IN_DAY + BIAS);
    secs = (int)(OSTicksToSeconds(ticks) % SECS_IN_DAY);
    if (secs < 0) {
        days -= 1;
        secs += SECS_IN_DAY;
    }

    fn_80210B7C(days, td);
    td->hour = secs / 60 / 60;
    td->min = secs / 60 % 60;
    td->sec = secs % 60;
}
