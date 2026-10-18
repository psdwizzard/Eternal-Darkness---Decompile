typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064CD30;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801139D4(void);

s32 fn_80016F78(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_801139D4();
    lbl_8064CD30 = 1;
    return 0;
}
