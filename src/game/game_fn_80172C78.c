extern int lbl_8064D18C;
extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80172C78(void* state)
{
    int value;

    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    value = lbl_8064D18C;
    lua_pushnumber(state, value);
    return 1;
}
