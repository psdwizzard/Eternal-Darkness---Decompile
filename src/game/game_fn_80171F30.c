extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_801AD72C(void);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];
extern const double lbl_806506A8;

int fn_80171F30(void* state)
{
    int result;

    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }
    result = fn_801AD72C();
    lua_pushnumber(state, result);
    return 1;
}
