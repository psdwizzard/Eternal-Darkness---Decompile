typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8014C23C(s32, s32, s32);

s32 fn_80019ED8(void* script)
{
    s32 first;
    s32 second;
    s32 third;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fn_8014C23C(first, second, third);
    return 0;
}
