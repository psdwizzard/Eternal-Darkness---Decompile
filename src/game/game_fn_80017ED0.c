typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_8014B888(s32, void**, s32*);
extern void fn_80198C8C(void*, s32, s32, s32, s32, s32);

s32 fn_80017ED0(void* script)
{
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    void* object;
    s32 unused;

    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    fn_8014B888(first, &object, &unused);
    if (object != 0) {
        fn_80198C8C(object, second, third, fourth, fifth, 0);
    }
    return 1;
}
