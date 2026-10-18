typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8014B990(s32, s32);
extern void fn_8014B928(void);

s32 fn_80018C14(void* script)
{
    if (lua_gettop(script) == 1) {
        fn_8014B990((s32)lua_tonumber(script, 1), 0);
    } else if (lua_gettop(script) == 0) {
        fn_8014B928();
    } else if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }
    return 1;
}
