extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801FD534(void*);
extern const char lbl_8024FF00[];

int fn_80174EB4(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    fn_801FD534((void *)fn_800F5C54(lua_tonumber(state, 1)));
    return 0;
}
