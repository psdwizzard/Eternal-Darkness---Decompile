typedef int s32;

extern s32 lbl_8064D180;
extern double lbl_8064DCE8;
extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);

s32 fn_8000A26C(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }
    lua_pushnumber(script, (double)lbl_8064D180);
    return 1;
}
