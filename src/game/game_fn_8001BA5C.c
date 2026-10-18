typedef int s32;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_8007D944(void);
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);
extern char lbl_8023BEF8[];
extern double lbl_8064DCF8;

s32 fn_8001BA5C(void* arg)
{
    if (lua_gettop(arg) != 0) {
        luaO_verror(arg, lbl_8023BEF8, 0, lua_gettop(arg));
        return 0;
    }

    if (fn_8007D944() != 0) {
        lua_pushnumber(arg, lbl_8064DCF8);
    } else {
        lua_pushnil(arg);
    }
    return 1;
}
