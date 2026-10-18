typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_801D10B8(void);

s32 fn_80013D54(void* script)
{
    s32 result;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    result = fn_801D10B8() != 0;
    lua_pushnumber(script, (double)result);
    return 1;
}
