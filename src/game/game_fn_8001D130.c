typedef int s32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80042818(s32);
extern void fn_80043708(s32);
extern char lbl_8023BEF8[];

s32 fn_8001D130(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    fn_80042818(value);
    fn_80043708(value);
    return 0;
}
