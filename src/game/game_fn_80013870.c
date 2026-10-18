typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern s32 fn_8011804C(s32);
extern void lua_pushnumber(void*, double);

s32 fn_80013870(void* script)
{
    void* parser = script;
    s32 result;

    if (lua_gettop(parser) != 1) {
        luaO_verror(parser, lbl_8023BEF8, 1, lua_gettop(parser));
        return 0;
    }

    result = fn_8011804C(fn_800F5C54(lua_tonumber(parser, 1)));
    lua_pushnumber(parser, (double)result);
    return 1;
}
