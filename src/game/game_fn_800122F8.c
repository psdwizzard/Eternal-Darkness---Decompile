typedef int s32;

char lbl_8023CA4C[] = "invalid args of %i";
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80025A78(int);

s32 fn_800122F8(void* script)
{
    void* parser;

    parser = script;
    switch (lua_gettop(parser)) {
    case 1:
        fn_80025A78((s32)lua_tonumber(parser, 1));
        break;
    case 0:
        fn_80025A78(1);
        break;
    default:
        luaO_verror(parser, lbl_8023CA4C, lua_gettop(parser));
        break;
    }
    return 0;
}
