typedef struct Value {
    int type;
    int unused;
    union {
        double number;
        void* pointer;
    } data;
} Value;

typedef struct Slot {
    void* fields[5];
    char pad14[44];
} Slot;

typedef struct State {
    Value* top;
    char pad04[0x40];
    Value* current;
    Slot* slots;
} State;

extern Value luaO_nilobject;
extern Value* luaH_getstr(Value*);
extern int luaT_tag(Value*);
extern Value* luaH_set(State*, Value*, Value*);
extern void luaD_checkstack(State*, int);
extern void luaD_call(State*, Value*, int);

void luaV_setglobal(State* state, void* payload)
{
    Value* value = luaH_getstr(state->current);
    void* target = state->slots[luaT_tag(value)].fields[4];

    if (target == 0) {
        if (value != &luaO_nilobject) {
            *value = state->top[-1];
        } else {
            Value argument;
            Value* result;

            argument.type = 3;
            argument.data.pointer = payload;
            value = state->top;
            result = luaH_set(state, state->current, &argument);
            *result = value[-1];
        }
        return;
    }

    luaD_checkstack(state, 3);
    state->top[2] = state->top[-1];
    state->top[1] = *value;
    state->top[0].type = 3;
    state->top[0].data.pointer = payload;
    state->top[-1].data.pointer = target;
    state->top[-1].type = 5;
    state->top += 3;
    luaD_call(state, state->top - 4, 0);
}
