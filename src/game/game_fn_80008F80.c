typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80008CA0(void);

s32 fn_80008F80(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_80008CA0();
    return 0;
}
