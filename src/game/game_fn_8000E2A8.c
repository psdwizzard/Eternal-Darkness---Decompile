typedef unsigned char u8;
typedef int s32;

typedef struct ValueSet {
    s32 values[10];
} ValueSet;

typedef struct RuntimeState {
    u8 pad[0x68];
    ValueSet* values;
} RuntimeState;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8000E2A8(void* script)
{
    s32 object_id;
    s32 selector;
    s32 first;
    s32 second;
    RuntimeState* state;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    object_id = (s32)lua_tonumber(script, 1);
    selector = (s32)lua_tonumber(script, 2);
    first = (s32)lua_tonumber(script, 3);
    second = (s32)lua_tonumber(script, 4);

    if (fn_80201814(object_id) != 0) {
        state = fn_80201B8C();
        switch (selector) {
        case 1:
            state->values->values[0] = first;
            break;
        case 2:
            state->values->values[1] = first;
            break;
        case 3:
            state->values->values[2] = first;
            state->values->values[3] = second;
            break;
        case 4:
            state->values->values[4] = first;
            state->values->values[5] = second;
            break;
        case 5:
            state->values->values[6] = first;
            state->values->values[7] = second;
            break;
        case 6:
            state->values->values[8] = first;
            state->values->values[9] = second;
            break;
        }
    }

    return 0;
}
