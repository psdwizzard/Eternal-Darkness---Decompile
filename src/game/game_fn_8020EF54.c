/* OSInitStopwatch. */

typedef long long s64;

typedef struct OSStopwatch {
    char* name;
    s64 total;
    unsigned long hits;
    s64 min;
    s64 max;
    s64 last;
    int running;
} OSStopwatch;

void fn_8020EF54(OSStopwatch* sw, char* name) {
    sw->name = name;
    sw->total = 0;
    sw->hits = 0;
    sw->min = 0xFFFFFFFFLL;
    sw->max = 0;
}
