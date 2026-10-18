extern void* lua_touserdata(void*, int);
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B54();
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_8016BE1C(void* state)
{
    void* object = lua_touserdata(state, 1);
    int result;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    result = fn_80201B54(object);
    lua_pushnumber(state, result);
    return 1;
}
