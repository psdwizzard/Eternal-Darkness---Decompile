typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_800C96D4(void*, s32, s32, s32, s32, s32, float);

s32 fn_80015888(void* script)
{
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    float fifth;
    s32 sixth;
    void* object;

    if (lua_gettop(script) != 6) {
        luaO_verror(script, lbl_8023BEF8, 6, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (float)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    object = fn_80201814(first);
    if (object != 0) {
        fn_800C96D4(object, second, third, fourth, sixth, 1, fifth);
    }
    return 0;
}
