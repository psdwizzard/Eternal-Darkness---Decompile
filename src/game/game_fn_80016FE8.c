typedef unsigned int u32;
typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern unsigned long long fn_8020123C();

s32 fn_80016FE8(void* script)
{
    u32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = fn_800F5C54(lua_tonumber(script, 1));
    fn_8020123C(0x9B, value, value, 0);
    return 0;
}
