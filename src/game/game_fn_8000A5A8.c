typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801288DC(void*, s32);

s32 fn_8000A5A8(void* script)
{
    s32 first;
    s32 second;
    void* object;
    void* result;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }
    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    object = fn_80201814(first);
    if (object != 0) {
        result = fn_80201BC8(object);
    } else {
        result = 0;
    }
    if (result != 0) {
        fn_801288DC(result, second);
    }
    return 0;
}
