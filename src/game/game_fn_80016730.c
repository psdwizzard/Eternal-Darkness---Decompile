typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800542D0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                       s32, s32, s32);

s32 fn_80016730(void* script)
{
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    s32 ninth;
    s32 tenth;
    s32 eleventh;
    s32 twelfth;
    s32 thirteenth;

    if (lua_gettop(script) != 13) {
        luaO_verror(script, lbl_8023BEF8, 13, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    eighth = (s32)lua_tonumber(script, 8);
    ninth = (s32)lua_tonumber(script, 9);
    tenth = (s32)lua_tonumber(script, 10);
    eleventh = (s32)lua_tonumber(script, 11);
    twelfth = (s32)lua_tonumber(script, 12);
    thirteenth = (s32)lua_tonumber(script, 13);
    fn_800542D0(first, second, third, fourth, fifth, sixth, seventh, eighth,
                ninth, tenth, eleventh, twelfth, thirteenth);
    return 0;
}
