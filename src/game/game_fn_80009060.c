typedef int s32;

extern const char lbl_8023BEF8[];
extern unsigned char lbl_8023BEE8[];

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80008C14(unsigned char*, s32, s32, s32);

s32 fn_80009060(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_80008C14(lbl_8023BEE8, 8, 2, 479);
    return 0;
}
