typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800C1B50(s32, s32, float, float, s32);

s32 fn_8000CDEC(void* script)
{
    s32 second;
    s32 first;
    float amount;
    float duration;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    amount = (float)lua_tonumber(script, 3);
    duration = (float)lua_tonumber(script, 4);
    fn_800C1B50(first, second, amount, duration, 0);
    return 0;
}
