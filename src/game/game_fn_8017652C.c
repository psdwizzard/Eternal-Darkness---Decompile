extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80206634(void*);
extern const char lbl_8024FF00[];

int fn_8017652C(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = fn_80206634(lua_touserdata(state, 1));
    lua_pushnumber(state, (double)value);
    return 1;
}
