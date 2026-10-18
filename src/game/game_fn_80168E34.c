typedef struct Value {
    int type;
    int unused;
    union {
        double number;
        void* pointer;
    } data;
} Value;

typedef struct Object {
    int unused;
    int index;
} Object;

typedef struct Slot {
    void* first;
    void* second;
    char pad08[56];
} Slot;

typedef struct State {
    Value* top;
    char pad04[0x44];
    Slot* slots;
} State;

extern Value* luaH_set(State*, Object*, Value*);
extern int luaT_tag(Value*);
extern void luaD_checkstack(State*, int);
extern void luaD_call(State*, Value*, int);
extern void luaG_typeerror(State*, Value*, char*);
extern char lbl_8064BBE8;

void luaV_settable(State* state, Value* key, Value* value)
{
    void* target;

    if (key->type == 4) {
        Object* object = key->data.pointer;
        int index = object->index;
        if (index == 4 || state->slots[index].second == 0) {
            Value* old_top = state->top;
            Value* result = luaH_set(state, object, value);
            *result = old_top[-1];
            return;
        }
    }

    target = state->slots[luaT_tag(key)].second;
    if (target != 0) {
        luaD_checkstack(state, 3);
        state->top[2] = state->top[-1];
        state->top[1] = *value;
        state->top[0] = *key;
        state->top[-1].data.pointer = target;
        state->top[-1].type = 5;
        state->top += 3;
        luaD_call(state, state->top - 4, 0);
    } else {
        luaG_typeerror(state, key, &lbl_8064BBE8);
    }
}
