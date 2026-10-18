typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8001D9FC(int);

s32 fn_80012278(void* script)
{
    s32 value;
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    value = (s32)lua_tonumber(parser, 1);
    fn_8001D9FC(value);
    return 0;
}
