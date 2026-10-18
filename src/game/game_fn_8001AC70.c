typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80087840(s32, float, s32, float, s32);

s32 fn_8001AC70(void* script)
{
    s32 arg1;
    float arg2;
    float arg4;
    s32 arg3;
    s32 arg5;

    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    arg1 = (s32)lua_tonumber(script, 1);
    arg2 = (float)lua_tonumber(script, 2);
    arg4 = (float)lua_tonumber(script, 3);
    arg3 = (s32)lua_tonumber(script, 4);
    arg5 = (s32)lua_tonumber(script, 5);
    fn_80087840(arg1, arg2, arg3, arg4, arg5);
    return 0;
}
