typedef int s32;
typedef unsigned int u32;

extern const char lbl_80244EDC[];
extern unsigned char lbl_8031CD84[];
extern s32 lbl_8064C8F0;

extern int lua_gettop(void *);
extern void luaO_verror(void *, const char *, ...);
extern void lua_pushnumber(void *, double);

s32 fn_8007F770(void *script)
{
    if (lua_gettop(script) != 0) {
        luaO_verror(script, lbl_80244EDC, 0, lua_gettop(script));
        return 0;
    }

    lua_pushnumber(script, (double)((u32 *)(lbl_8031CD84 + 0x444))[lbl_8064C8F0 * 2]);
    return 1;
}
