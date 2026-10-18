typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern s32 fn_80046378(s32, void*, s32);
extern void lua_pushnumber(void*, double);

s32 fn_80017CC8(void* script)
{
    s32 first;
    void* second;
    s32 third;
    s32 value;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = lua_touserdata(script, 2);
    third = (s32)lua_tonumber(script, 3);
    value = fn_80046378(first, second, third);
    lua_pushnumber(script, (double)value);
    return 1;
}
