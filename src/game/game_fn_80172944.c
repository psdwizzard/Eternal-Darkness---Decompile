extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_800460EC(void);
extern const char lbl_8024FF00[];
extern const double lbl_806506D8;

int fn_80172944(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    if (fn_800460EC() != 0) {
        lua_pushnumber(state, lbl_806506D8);
    } else {
        lua_pushnil(state);
    }
    return 1;
}
