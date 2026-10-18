typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_801E2068(s32);
extern void lua_pushnumber(void*, double);

s32 fn_8000C17C(void* script)
{
    s32 result;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    result = fn_801E2068((s32)lua_tonumber(script, 1));
    lua_pushnumber(script, result);
    return 1;
}
