typedef unsigned long long u64;
typedef int s32;
typedef unsigned int u32;

typedef struct {
    unsigned char pad[0x38];
    s32 value;
} CommandArgument;

typedef struct {
    unsigned char pad[0xC4];
    CommandArgument* argument;
} CommandState;

typedef struct {
    unsigned char pad[0x38];
    CommandState* state;
} CommandOwner;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern int fn_80201B54();
extern void *fn_80201B8C();
extern unsigned long long fn_8020123C();

s32 fn_80019C10(void* script)
{
    register s32 value;
    register s32 result;
    register void* object;
    register void* script_arg = script;

    if (lua_gettop(script_arg) != 1) {
        luaO_verror(script_arg, lbl_8023BEF8, 1, lua_gettop(script_arg));
        return 0;
    }

    value = (s32)lua_tonumber(script_arg, 1);
    result = 0;
    object = fn_80204844(fn_80201B9C(), 0x20);
    if (object != 0) {
        s32 id = fn_80201B54(object);
        CommandState* state = ((CommandOwner*)fn_80201B8C(object))->state;
        u32 message_result;
        state->argument->value = value;
        message_result = fn_8020123C(0x53, 0, id, &state->argument->value) &
                         0xFFFFFFFFULL;
        if (message_result == 1) {
            result = 1;
        }
    }

    lua_pushnumber(script_arg, result);
    return 1;
}
