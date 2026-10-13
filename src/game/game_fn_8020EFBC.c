/* fn_8020EFBC (0x8020EFBC, 204 bytes): OSStopStopwatch. */

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

void fn_8020EFBC(OSStopwatch* sw) {
    s64 interval;

    if (sw->running) {
        interval = (s64)OSGetTime() - sw->last;
        sw->total += interval;
        sw->running = 0;
        sw->hits++;
        if (sw->max < interval) {
            sw->max = interval;
        }
        if (interval < sw->min) {
            sw->min = interval;
        }
    }
}
