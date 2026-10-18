typedef unsigned char u8;
typedef int s32;

typedef struct Ref Ref;

typedef struct State {
    u8 pad[0x7C];
    s32 value;
} State;

typedef struct Object {
    State* state;
} Object;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void *fn_80201814();
extern void *fn_80201B8C();
extern char lbl_8023BEF8[];

s32 fn_8001C250(void* arg)
{
    Ref* ref = fn_80201814(fn_80201B44());
    s32 value;

    if (lua_gettop(arg) != 1) {
        luaO_verror(arg, lbl_8023BEF8, 1, lua_gettop(arg));
        return 0;
    }

    value = (s32)lua_tonumber(arg, 1);
    if (ref != 0) {
        Object* object = fn_80201B8C(ref);
        State* state = object != 0 ? object->state : 0;
        state->value = value;
    }
    return 0;
}
