typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201AE4(void);
extern void fn_801D7E70(void*, s32);

s32 fn_80019B88(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    fn_801D7E70((void*)fn_80201AE4(), value);
    return 0;
}
