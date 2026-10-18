typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801291F0(void*, s32, s32);

s32 fn_80009E70(void* script)
{
    s32 second;
    s32 third;
    s32 first;
    void* object;
    void* target;

    if (lua_gettop(script) != 3) {
        luaO_verror(script, lbl_8023BEF8, 3, lua_gettop(script));
        return 0;
    }
    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    object = fn_80201814(first);
    if (object != 0) {
        target = fn_80201BC8(object);
    } else {
        target = 0;
    }
    if (object != 0 && target != 0) {
        fn_801291F0(target, second, third);
    }
    return 0;
}
