typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064C55C;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);

s32 fn_8000D354(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    lbl_8064C55C = (s32)lua_tonumber(script, 1);
    return 0;
}
