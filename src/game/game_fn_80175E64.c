extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern int fn_800467F0(int, int);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80175E64(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }
    value = lua_tonumber(state, 1);
    value = fn_800467F0(value, 0);
    lua_pushnumber(state, (double)value);
    return 1;
}
