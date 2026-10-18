typedef unsigned short u16;
typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801FA4F0(s32, u16);

s32 fn_8001A4C8(void* script)
{
    s32 first;
    u16 second;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (u16)(s32)lua_tonumber(script, 2);
    fn_801FA4F0(first, second);
    return 0;
}
