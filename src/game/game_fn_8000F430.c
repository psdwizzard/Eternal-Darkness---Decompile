typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801A5910(s32);

s32 fn_8000F430(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }
    fn_801A5910((s32)lua_tonumber(script, 1));
    return 0;
}
