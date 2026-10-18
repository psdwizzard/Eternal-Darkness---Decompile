typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_800835CC(s32);

s32 fn_8001AAB8(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = fn_800835CC((s32)lua_tonumber(script, 1));
    if (value >= 0) {
        lua_pushnumber(script, (double)value);
    } else {
        lua_pushnil(script);
    }
    return 1;
}
