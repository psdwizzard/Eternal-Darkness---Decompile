extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern int fn_802066E0(int, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80172BB0(void* state)
{
    int first;
    int second;
    int result;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = fn_800F5C54(lua_tonumber(state, 2));
    result = fn_802066E0(first, second);
    lua_pushnumber(state, result);
    return 1;
}
