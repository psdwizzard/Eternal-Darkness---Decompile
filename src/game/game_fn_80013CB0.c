typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_801D3C5C(s32);

s32 fn_80013CB0(void* script)
{
    s32 value;
    s32 result;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    result = fn_801D3C5C(value);
    lua_pushnumber(script, (double)result);
    return 1;
}
