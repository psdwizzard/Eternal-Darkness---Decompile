typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 unknown0;
    u32 unknown4;
    u32 unknown8;
} Entry;

typedef struct RangeState {
    int distance;
    int span;
    Entry* previous;
    Entry* current;
} RangeState;

extern int fn_801285C0(Entry*);

#define ABS(x) ((x) < 0 ? -(x) : (x))

int fn_80127714(Entry* entries, u16 count, RangeState* state, int step,
                int value, int update)
{
    int found;
    int status;
    Entry* current;
    Entry* last;
    Entry* previous;

    found = 0;
    status = 0;
    last = entries;
    state->distance = 0;
    if (step >= 0) {
        step = 1;
    } else {
        step = -1;
    }
    if (step == 1) {
        last += count - 1;
    }
    if (update == 0) {
        if (step == 1) {
            previous = entries;
            current = entries + 1;
        } else {
            previous = entries + (count - 1);
            current = entries + (count - 2);
        }
    } else if (step == 1) {
        current = entries;
    } else {
        current = entries + (count - 1);
    }

    while (status == 0) {
        if ((step >= 0 && value <= fn_801285C0(current)) ||
            (step < 0 && fn_801285C0(current) <= value)) {
            status = 1;
            if (update == 0) {
                state->previous = previous;
            }
            state->current = current;
            if (update != 0) {
                state->span += ABS(fn_801285C0(current) - value);
            } else {
                state->span = ABS(fn_801285C0(current) - fn_801285C0(previous));
                state->distance = ABS(value - fn_801285C0(previous));
            }
            found = 1;
        } else if (current == last) {
            status = 2;
            if (update == 0) {
                state->previous = last - step;
            }
            state->current = last;
            if (update != 0) {
                state->span += ABS(fn_801285C0(current) - value);
            } else {
                state->span = ABS(fn_801285C0(current) - fn_801285C0(previous));
            }
            found = 1;
        } else {
            if (update == 0) {
                previous = current;
            }
            current += step;
        }
    }
    return found;
}
