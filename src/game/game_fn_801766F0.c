extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80049774(int);
extern const char lbl_8024FF00[];

int fn_801766F0(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }
    fn_80049774((int)lua_tonumber(state, 1));
    return 0;
}
