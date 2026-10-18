extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_800473AC(void);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];
extern const double lbl_806506A8;

int fn_8017138C(void* state)
{
    int value;

    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    value = fn_800473AC();
    lua_pushnumber(state, value);
    return 1;
}
