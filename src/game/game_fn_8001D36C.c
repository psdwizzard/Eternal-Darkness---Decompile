typedef int s32;

char lbl_8023CF58[20] = "EDResetWeaponAnims";

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_8007D69C(void*);
extern char lbl_8023BEF8[];

s32 fn_8001D36C(void* script)
{
    void* object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    object = fn_80201814((s32)lua_tonumber(script, 1));
    if (object != 0) {
        fn_8007D69C(object);
    }
    return 0;
}
