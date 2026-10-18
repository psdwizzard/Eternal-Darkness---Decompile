typedef unsigned int u32;
typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern unsigned long long fn_8020123C();

s32 fn_80017074(void* script)
{
    u32 value;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    value = fn_800F5C54(lua_tonumber(script, 1));
    if (fn_800F5C54(lua_tonumber(script, 2)) == 1) {
        fn_8020123C(0xB1, value, value, 0);
    } else {
        fn_8020123C(0xD0, value, value, 0);
    }
    return 0;
}
