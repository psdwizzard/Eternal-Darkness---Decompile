typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
/* ABI adapter: this matching caller intentionally reuses the live f1 value. */
extern unsigned int fn_800F5C54(double);
extern void fn_800C9508(s32, s32);

s32 fn_80009D54(void* script)
{
    s32 value;
    register s32 current;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }
    value = (s32)lua_tonumber(script, 1);
    current = fn_800F5C54(lua_tonumber(script, 2));
    fn_800C9508(value, current);
    return 0;
}
