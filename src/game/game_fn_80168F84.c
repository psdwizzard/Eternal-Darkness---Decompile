typedef struct Value {
    int type;
    int unused;
    union {
        double number;
        void* pointer;
    } data;
} Value;

typedef struct Slot {
    void* first;
    void* second;
    void* third;
    void* fourth;
    char pad10[48];
} Slot;

typedef struct State {
    Value* top;
    char pad04[0x40];
    Value* current;
    Slot* slots;
} State;

extern Value* luaH_getstr(Value*);
extern int luaT_tag(Value*);
extern void luaD_checkstack(State*, int);
extern void luaD_call(State*, Value*, int);

Value* luaV_getglobal(State* state, void* payload)
{
    Value* value = luaH_getstr(state->current);
    void* target = state->slots[luaT_tag(value)].fourth;

    if (target == 0)
        return value;

    luaD_checkstack(state, 3);
    state->top[0].data.pointer = target;
    state->top[0].type = 5;
    state->top[1].data.pointer = payload;
    state->top[1].type = 3;
    state->top[2] = *value;
    state->top += 3;
    luaD_call(state, state->top - 3, 1);
    return state->top - 1;
}
