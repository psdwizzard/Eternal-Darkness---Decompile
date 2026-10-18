typedef signed char s8;
typedef unsigned char u8;
typedef int s32;

extern const char lbl_8023BEF8[];
extern u8 lbl_8030F540[];
extern const double lbl_8064DE18;
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_8015E4E8(void);
extern void lua_pushnumber(void*, double);

s32 fn_80016B24(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    if (fn_8015E4E8() != 0) {
        lua_pushnumber(script, (double)(s8)lbl_8030F540[0x1E0]);
        return 1;
    }

    lua_pushnumber(script, lbl_8064DE18);
    return 1;
}
