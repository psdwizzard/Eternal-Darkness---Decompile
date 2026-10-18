/* OSStartStopwatch (0x8020EF80, 60 bytes): OSStartStopwatch. */

typedef unsigned long long u64;
typedef long long s64;
typedef u64 OSTime;

OSTime OSGetTime(void);

typedef struct OSStopwatch {
    char* name;
    s64 total;
    unsigned long hits;
    s64 min;
    s64 max;
    s64 last;
    int running;
} OSStopwatch;

void OSStartStopwatch(OSStopwatch* sw) {
    sw->running = 1;
    sw->last = (s64)OSGetTime();
}
