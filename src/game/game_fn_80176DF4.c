extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80204888(int);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_80176DF4(void* state)
{
    int id;
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    id = (int)lua_tonumber(state, 1);
    value = fn_80204888(id);
    lua_pushnumber(state, (double)value);
    return 1;
}
