typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCF8;
extern s32 fn_8007FAC0(void);
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnil(void*);
extern void lua_pushnumber(void*, double);

s32 fn_8000DFCC(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    if (fn_8007FAC0() != 0) {
        lua_pushnumber(script, lbl_8064DCF8);
    } else {
        lua_pushnil(script);
    }
    return 1;
}
