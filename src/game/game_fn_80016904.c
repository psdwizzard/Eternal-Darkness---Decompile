typedef unsigned char u8;
typedef int s32;

extern const char lbl_8023BEF8[];
extern u8 lbl_8030F540[];
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);

s32 fn_80016904(void* script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_8023BEF8, 0, lua_gettop(script));
        return 0;
    }

    lua_pushnumber(script, (double)lbl_8030F540[0x1DA]);
    return 1;
}
