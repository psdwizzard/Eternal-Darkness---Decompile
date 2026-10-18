extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801E8EFC(int, int);
extern const char lbl_8024FF00[];

int fn_80176E98(void* state)
{
    int first;
    int second;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    fn_801E8EFC(first, second);
    return 0;
}
