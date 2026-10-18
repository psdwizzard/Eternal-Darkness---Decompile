extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80045BE0(int);
extern const char lbl_8024FF00[];

int fn_801729CC(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = lua_tonumber(state, 1);
    fn_80045BE0(value);
    return 0;
}
