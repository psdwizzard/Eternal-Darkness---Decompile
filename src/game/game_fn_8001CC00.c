typedef int s32;

char lbl_8023CDFC[28] = "EDCreateEnchantedExplosion";

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern s32 lbl_8064C5D8;
extern char lbl_8023BEF8[];

s32 fn_8001CC00(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    lbl_8064C5D8 = 1;
    return 0;
}
