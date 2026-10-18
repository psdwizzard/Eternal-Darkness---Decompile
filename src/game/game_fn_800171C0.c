typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064CDC8;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);

s32 fn_800171C0(void* script)
{
    s32 value = lbl_8064CDC8 == 3;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    lua_pushnumber(script, value);
    return 1;
}
