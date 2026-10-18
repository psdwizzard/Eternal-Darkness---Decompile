typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064CAB4;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);

s32 fn_80016CE8(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    lbl_8064CAB4 = (s32)lua_tonumber(script, 1);
    return 0;
}
