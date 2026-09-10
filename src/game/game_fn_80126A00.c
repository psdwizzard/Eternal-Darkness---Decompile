typedef unsigned int u32;

typedef struct Entry {
    u32 key;
    float value;
} Entry;

typedef struct EntryList {
    u32 count;
    Entry* entries;
} EntryList;

typedef struct SearchState {
    u32 key;
    int direction;
    int distance;
    int span;
    Entry* current;
    Entry* previous;
} SearchState;

extern float lbl_80650188;
extern int fn_8012692C(Entry*, int, SearchState*);

int fn_80126A00(EntryList* list, SearchState* state, int amount, float* output)
{
    int should_search;
    int movement;
    int result;
    Entry* previous;
    Entry* current;
    float value;

    value = lbl_80650188;
    result = 0;
    if (state->direction == 0) {
        state->direction = 1;
    }

    movement = amount * state->direction;
    state->key += movement;
    state->distance += movement < 0 ? -movement : movement;

    should_search = 0;
    if (list->count != 0 && state->distance > state->span) {
        should_search = 1;
    }
    if (should_search != 0) {
        result = fn_8012692C(list->entries, list->count, state);
    }

    previous = state->previous;
    current = state->current;
    if (list->count != 0 && result == 0) {
        value = previous->value +
            ((float)state->distance / (float)state->span) *
                (current->value - previous->value);
    }
    *output = value;
    return result;
}
