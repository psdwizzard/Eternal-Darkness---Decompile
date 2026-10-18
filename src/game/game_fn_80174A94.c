extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80046D38(int);
extern const char lbl_8024FF00[];

int fn_80174A94(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    fn_80046D38(lua_tonumber(state, 1));
    return 0;
}
