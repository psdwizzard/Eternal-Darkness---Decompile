/* fn_8020F088 (0x8020F088, 112 bytes): OSCheckStopwatch. */

typedef long long s64;
typedef unsigned long long OSTime;

extern OSTime OSGetTime(void);

typedef struct OSStopwatch {
    char* name;
    s64 total;
    unsigned long hits;
    s64 min;
    s64 max;
    s64 last;
    int running;
} OSStopwatch;

s64 fn_8020F088(OSStopwatch* sw) {
    s64 total = sw->total;

    if (sw->running) {
        total += (s64)OSGetTime() - sw->last;
    }
    return total;
}
