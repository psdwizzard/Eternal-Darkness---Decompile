extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AD490(void);
extern const char lbl_8024FF00[];

int fn_801720E8(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    fn_801AD490();
    return 0;
}
