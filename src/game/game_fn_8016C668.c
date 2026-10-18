extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801B0CA4(int, int);
extern const char lbl_8024FF00[];

int fn_8016C668(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    fn_801B0CA4(-1, (int)lua_tonumber(state, 1));
    return 0;
}
