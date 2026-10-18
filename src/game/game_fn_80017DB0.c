typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern s32 fn_80046398(s32, s32, s32, s32);
extern void lua_pushnumber(void*, double);

s32 fn_80017DB0(void* script)
{
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    s32 value;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    if (first != 0) {
        second = 0xFFFF;
    }
    value = fn_80046398(first, second, third, fourth);
    lua_pushnumber(script, (double)value);
    return 1;
}
