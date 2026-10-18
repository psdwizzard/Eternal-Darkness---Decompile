extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern int fn_801B243C(void);
extern const char lbl_8024FF00[];
extern const double lbl_806506A8;

int fn_8017250C(void* state)
{
    int value;

    value = fn_801B243C();
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    lua_pushnumber(state, value);
    return 1;
}
