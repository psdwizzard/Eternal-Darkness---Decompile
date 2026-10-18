typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800EABD8(s32);

s32 fn_80011F00(void* script)
{
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 0) {
        luaO_verror(parser, lbl_8023BEF8, 0, lua_gettop(parser));
        return 0;
    }

    fn_800EABD8(0);
    return 0;
}
