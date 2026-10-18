typedef int s32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C4E0;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801E7974(void*, int);
extern void fn_801E79A0(void*, s32);

s32 fn_80016C48(void* script)
{
    s32 enabled;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    enabled = (s32)lua_tonumber(script, 1);
    if (enabled != 0) {
        fn_801E7974(lbl_8064C4E0, 0x2ED);
    } else {
        fn_801E79A0(lbl_8064C4E0, 0x2ED);
    }
    return 0;
}
