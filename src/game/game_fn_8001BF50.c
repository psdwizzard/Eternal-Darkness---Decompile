typedef int s32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80071FF8(s32);
extern char lbl_8023BEF8[];

s32 fn_8001BF50(void* arg)
{
    if (lua_gettop(arg) != 1) {
        luaO_verror(arg, lbl_8023BEF8, 1, lua_gettop(arg));
        return 0;
    }

    fn_80071FF8((s32)lua_tonumber(arg, 1));
    return 0;
}
