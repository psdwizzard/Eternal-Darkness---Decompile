typedef int s32;

extern s32 lbl_8064D18C;
extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800CCDA8(s32, s32);

s32 fn_8000A37C(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }
    fn_800CCDA8((s32)lua_tonumber(script, 1), lbl_8064D18C);
    return 1;
}
