typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern void* fn_80201B3C();
extern void* fn_80205288(void);
extern int fn_80201B54();

s32 fn_8000DA50(void* script)
{
    s32 value;
    void* object;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_80201B3C();
    object = fn_80205288();
    value = object != 0 ? fn_80201B54(object) : 0;
    lua_pushnumber(script, (double)value);
    return 1;
}
