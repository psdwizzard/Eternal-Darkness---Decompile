typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_80088F08(s32, s32);

s32 fn_80017B80(void* script)
{
    s32 first;
    s32 second;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    if (((first != 1) && (first != 0)) || (second != 1)) {
        first = 0;
        second = 1;
    }
    fn_80088F08(first, second);
    return 0;
}
