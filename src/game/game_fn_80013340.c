typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern s32 lbl_8064C61C;
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);

s32 fn_80013340(void* script)
{
    void* parser = script;

    if (lua_gettop(parser) != 0) {
        luaO_verror(parser, lbl_8023BEF8, 0, lua_gettop(parser));
        return 0;
    }

    lua_pushnumber(parser, (double)lbl_8064C61C);
    return 1;
}
