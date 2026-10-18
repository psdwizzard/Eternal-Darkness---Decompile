extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F5980(void);
extern const char lbl_8024FF00[];

int fn_801751DC(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    fn_801F5980();
    return 0;
}
