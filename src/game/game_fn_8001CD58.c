typedef unsigned int u32;
typedef int s32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern u32 fn_800AD2AC(void);
extern const double lbl_8064DE18;
extern char lbl_8023BEF8[];

s32 fn_8001CD58(void* script)
{
    double result = lbl_8064DE18;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    switch ((s32)lua_tonumber(script, 1)) {
    case 1:
        result = (double)fn_800AD2AC();
        break;
    }

    lua_pushnumber(script, result);
    return 1;
}
