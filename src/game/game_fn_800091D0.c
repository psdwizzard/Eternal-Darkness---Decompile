typedef int s32;

extern const char lbl_8023BEF8[];
extern unsigned char lbl_8064A9B0[8];

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80008C14(unsigned char*, s32, s32, s32);

s32 fn_800091D0(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_80008C14(lbl_8064A9B0, 5, 1, 67);
    return 0;
}
