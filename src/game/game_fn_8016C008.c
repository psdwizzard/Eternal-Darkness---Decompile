extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern const char lbl_8024FF00[];

int fn_8016C008(void* state)
{
    int first;
    int second;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    fn_801B05E8(first, second, 4, 0, 0, 5, 0, 0);
    return 0;
}
