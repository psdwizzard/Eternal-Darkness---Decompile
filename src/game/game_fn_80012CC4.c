typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C50C;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_80027730(void*, s32, s32);

s32 fn_80012CC4(void* script)
{
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 4 && lua_gettop(parser) != 3) {
        luaO_verror(parser, lbl_8023BEF8, 3, lua_gettop(parser));
        return 0;
    }

    fn_80027730(
        fn_801E6CA0(
            lbl_8064C50C,
            fn_800F5C54(lua_tonumber(parser, 1)),
            fn_800F5C54(lua_tonumber(parser, 2)),
            0,
            1),
        (s32)lua_tonumber(parser, 3),
        0);
    return 0;
}
