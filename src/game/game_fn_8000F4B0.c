typedef int s32;

#pragma use_lmw_stmw on

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern s32 fn_800CB098(s32, s32, s32, s32, s32, s32);

s32 fn_8000F4B0(void* script)
{
    s32 third;
    s32 fourth;
    s32 first;
    s32 second;
    s32 fifth;
    s32 result;

    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    result = fn_800CB098(first, second, third, fourth, fifth, 0);
    lua_pushnumber(script, (double)result);
    return 1;
}
