extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801441C0(int, int, int);
extern const char lbl_8024FF00[];

int fn_80176BA4(void* state)
{
    int first;
    int second;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    fn_801441C0(first, second, (int)lua_tonumber(state, 3));
    return 0;
}
