typedef int s32;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern void *fn_8006D444(void);
extern s32 fn_8006BCE4(void);
extern void lua_pushnumber(void*, double);

s32 fn_80017A3C(void* script)
{
    s32 value;

    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    fn_80204844(fn_80201B9C(), 0x20);
    fn_8006D444();
    value = fn_8006BCE4();
    if (value == -1) {
        value = 0;
    }
    lua_pushnumber(script, (double)value);
    return 1;
}
