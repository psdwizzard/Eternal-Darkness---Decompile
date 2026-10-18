typedef struct Value {
    int type;
    int unused;
    double data;
} Value;

typedef struct State {
    Value* top;
    char pad04[0x44];
    struct CallbackSet* callbacks;
} State;

typedef struct CallbackSet {
    void* values[16];
} CallbackSet;

extern void* luaT_eventname[];
extern int luaT_tag(Value*);
extern void lua_pushstring(State*, void*);
extern void luaD_callTM(State*, void*, int, int);

int call_binTM(State* state, Value* value, int index)
{
    void* callback = state->callbacks[luaT_tag(value - 2)].values[index];

    state->top = value;
    if (callback == 0) {
        callback = state->callbacks[luaT_tag(value - 1)].values[index];
        if (callback == 0) {
            callback = state->callbacks[0].values[index];
            if (callback == 0) {
                return 0;
            }
        }
    }

    lua_pushstring(state, luaT_eventname[index]);
    luaD_callTM(state, callback, 3, 1);
    return 1;
}
