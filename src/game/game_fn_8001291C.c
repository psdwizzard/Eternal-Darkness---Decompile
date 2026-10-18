typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064CD2C;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);

s32 fn_8001291C(void* script)
{
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    lbl_8064CD2C = (s32)lua_tonumber(parser, 1);
    return 0;
}
