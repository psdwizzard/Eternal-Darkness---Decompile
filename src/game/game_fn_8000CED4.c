typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800C1B50(s32, s32, float, float, s32);

s32 fn_8000CED4(void* script)
{
    s32 object;
    float value0;
    float value1;
    float value2;
    float value3;
    float value4;

    if (lua_gettop(script) != 6) {
        luaO_verror(script, lbl_8023BEF8, 6, lua_gettop(script));
        return 0;
    }

    object = (s32)lua_tonumber(script, 1);
    value0 = (float)lua_tonumber(script, 2);
    value1 = (float)lua_tonumber(script, 3);
    value2 = (float)lua_tonumber(script, 4);
    value3 = (float)lua_tonumber(script, 5);
    value4 = (float)lua_tonumber(script, 6);
    fn_800C1B50(object, 15, value0, value0, 0);
    fn_800C1B50(object, 0, value1, value1, 0);
    fn_800C1B50(object, 1, value2, value2, 0);
    fn_800C1B50(object, 2, value3, value3, 0);
    fn_800C1B50(object, 3, value4, value4, 0);
    return 0;
}
