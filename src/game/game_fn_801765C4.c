extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800486A8(int);
extern const char lbl_8024FF00[];

int fn_801765C4(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    fn_800486A8((int)lua_tonumber(state, 1));
    return 0;
}
