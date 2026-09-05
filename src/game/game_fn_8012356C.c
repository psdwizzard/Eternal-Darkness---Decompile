typedef struct State {
    unsigned char pad[0x248];
    int mode;
} State;

typedef struct Item {
    float value;
    unsigned char pad4[0x18];
    State* state;
} Item;

#pragma opt_propagation off
int fn_8012356C(const Item* first, const Item* second)
{
    State* second_state = *(State* const volatile*)&second->state;
    State* first_state = first->state;
    int first_mode = first_state->mode;
    float first_value = *(const volatile float*)&first->value;
    float second_value = *(const volatile float*)&second->value;
    int second_mode = second_state->mode;
    int result;

    if (first_mode > 2) {
        first_mode = 0;
    } else if (first_mode == 0) {
        first_mode = 3;
    }

    if (second_mode > 2) {
        second_mode = 0;
    } else if (second_mode == 0) {
        second_mode = 3;
    }

    result = first_mode - second_mode;
    if (second_mode == first_mode) {
        result = (int)(first_value - second_value);
    }
    return result;
}
#pragma opt_propagation reset
