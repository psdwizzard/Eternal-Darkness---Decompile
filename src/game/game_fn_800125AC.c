typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern u32 lbl_8064CCD8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);

s32 fn_800125AC(void* script)
{
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    lbl_8064CCD8 = fn_800F5C54(lua_tonumber(parser, 1));
    return 0;
}
