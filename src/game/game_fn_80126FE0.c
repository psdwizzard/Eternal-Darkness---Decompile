#pragma use_lmw_stmw on
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

int fn_80126FE0(Entry* entries, u16 count, RangeState* state, int direction,
                int value)
{
    int step;
    int stride;
    int result;
    int done;
    Entry* previous;
    Entry* current;
    int current_value;
    int previous_value;
    int delta;
    int span;
    Entry* end;

    end = entries;
    result = 0;
    done = 0;
    step = -1;
    previous = state->previous;
    current = state->current;
    if (direction >= 0) {
        step = 1;
    }
    if (step == 1) {
        end += count - 1;
    }
    stride = step * 12;
    while (done == 0) {
        current_value = fn_801285C0(current);
        if ((step >= 0 && value <= current_value) ||
            (step < 0 && current_value <= value)) {
            previous_value = fn_801285C0(previous);
            done = 1;
            state->previous = previous;
            state->current = current;
            delta = value - previous_value;
            if (delta < 0) {
                delta = 0U - (u32)delta;
            }
            state->distance = delta;
            span = current_value - previous_value;
            if (span < 0) {
                span = 0U - (u32)span;
            }
            state->span = span;
        } else if (current == end) {
            done = 2;
            result = 1;
        } else {
            previous = current;
            current = (Entry*)((u8*)current + stride);
        }
    }
    return result;
}
#pragma use_lmw_stmw off
