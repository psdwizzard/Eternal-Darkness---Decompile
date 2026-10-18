typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064C598;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);

s32 fn_8000BE60(void* script)
{
    s32 value = (s32)lua_tonumber(script, 1);

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    lbl_8064C598 = value != 0;
    return 0;
}
