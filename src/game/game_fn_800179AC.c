typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_800462C8(s32);
extern void lua_pushnumber(void*, double);

s32 fn_800179AC(void* script)
{
    s32 value;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    value = fn_800462C8(1);
    lua_pushnumber(script, (double)value);
    return 1;
}
