typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void fn_801E20D0(void);

s32 fn_80016BDC(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_80201B44();
    fn_801E20D0();
    return 0;
}
