typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8011FF30(s32);

s32 fn_8000BF4C(void* script)
{
    s32 value = (s32)lua_tonumber(script, 1);

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    if (value != 0) {
        fn_8011FF30(value);
    } else {
        fn_8011FF30(value);
    }
    return 0;
}
