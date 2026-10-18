typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801CFFE8(s32, s32, s32, s32);

s32 fn_800139F0(void* script)
{
    void* parser = script;
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;

    if (lua_gettop(parser) != 4) {
        luaO_verror(parser, lbl_8023BEF8, 4, lua_gettop(parser));
        return 0;
    }

    first = (s32)lua_tonumber(parser, 1);
    second = (s32)lua_tonumber(parser, 2);
    third = (s32)lua_tonumber(parser, 3);
    fourth = (s32)lua_tonumber(parser, 4);
    fn_801CFFE8(first, second, third, fourth);
    return 0;
}
