typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801D16E4(s32, s32);

s32 fn_80013EEC(void* script)
{
    s32 first;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    fn_801D16E4(first, (s32)lua_tonumber(script, 2));
    return 0;
}
