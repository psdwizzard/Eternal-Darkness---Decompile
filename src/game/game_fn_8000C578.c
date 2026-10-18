typedef int s32;
typedef unsigned char u8;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801E1B04(s32, u8);

s32 fn_8000C578(void* script)
{
    s32 value;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    fn_801E1B04(value, (u8)(s32)lua_tonumber(script, 2));
    return 0;
}
