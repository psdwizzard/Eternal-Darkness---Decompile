typedef unsigned short u16;

typedef struct RangeState {
    int distance;
    int span;
    void* previous;
    void* current;
} RangeState;

typedef struct MotionState {
    int value;
    int multiplier;
    int wrapped;
    RangeState first;
    int pad1C;
    int pad20;
    int pad24;
    RangeState second;
} MotionState;

typedef struct MotionSource {
    u16 first_count;
    u16 pad2;
    void* first_entries;
    u16 second_count;
    u16 padA;
    void* second_entries;
} MotionSource;

extern int fn_80126FE0(void*, u16, RangeState*, int, int);

#pragma use_lmw_stmw on
int fn_80126E80(MotionSource* source, MotionState* state, int amount)
{
    int first_done;
    int second_done;
    int delta;
    int result;
    RangeState* first;
    RangeState* second;

    result = 0;
    if (state->multiplier == 0) {
        state->multiplier = 1;
    }
    delta = amount * state->multiplier;
    first = &state->first;
    second = &state->second;
    if (state->wrapped == 0) {
        state->value += delta;
    }
    first->distance += delta < 0 ? -delta : delta;
    second->distance += delta < 0 ? -delta : delta;

    first_done = 0;
    if (source->first_count != 0 &&
        first->distance > first->span) {
        first_done = 1;
    }
    second_done = 0;
    if (source->second_count != 0 &&
        second->distance > second->span) {
        second_done = 1;
    }
    if ((first_done != 0 || second_done != 0) && state->wrapped != 0) {
        state->value += delta;
        state->wrapped = 0;
    }
    if (first_done != 0) {
        result = fn_80126FE0(source->first_entries, source->first_count,
                            first, state->multiplier, state->value);
    }
    if (second_done != 0) {
        result |= fn_80126FE0(source->second_entries, source->second_count,
                             second, state->multiplier, state->value);
    }
    return result;
}
#pragma use_lmw_stmw off
