typedef int s32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80047080(s32);
extern char lbl_8023BEF8[];

s32 fn_8001CF38(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    fn_80047080((s32)lua_tonumber(script, 1));
    return 0;
}
