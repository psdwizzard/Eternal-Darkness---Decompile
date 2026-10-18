extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern int fn_801B002C(int, int, int, int, int);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_8016C164(void* state)
{
    int first;
    int result;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    result = fn_801B002C(first, (int)lua_tonumber(state, 2), 1, 0, 0);
    lua_pushnumber(state, result);
    return 1;
}
