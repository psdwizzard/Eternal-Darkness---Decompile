extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8015C7D8(int);
extern const char lbl_8024FF00[];

int fn_80172A4C(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = lua_tonumber(state, 1);
    fn_8015C7D8(value);
    return 0;
}
