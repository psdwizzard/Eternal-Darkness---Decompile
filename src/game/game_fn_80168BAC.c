typedef struct Value {
    int type;
    int unused;
    union {
        double number;
        void* pointer;
    } data;
} Value;

typedef struct State {
    Value* top;
    char pad04[4];
    Value* limit;
} State;

extern Value* luaF_newclosure(State*);
extern void luaD_checkstack(State*, int);

Value* luaV_closure(State* state, int count)
{
    Value* result = luaF_newclosure(state);
    int offset = count * sizeof(Value);
    Value* destination;

    state->top = (Value*)((char*)state->top - offset);
    destination = (Value*)((char*)result + offset);
    goto test;
copy:
        *(Value*)((char*)destination + sizeof(Value)) =
            *(Value*)((char*)state->top + offset);
test:
    {
        int more = count--;
        offset -= sizeof(Value);
        destination--;
        if (more != 0)
        goto copy;
    }

    state->top->data.pointer = result;
    state->top->type = 5;
    if (state->top == state->limit)
        luaD_checkstack(state, 1);
    state->top++;
    return result;
}
