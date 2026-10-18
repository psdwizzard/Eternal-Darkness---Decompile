extern void* fn_801FD24C(void);
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80175244(void* state)
{
    fn_801FD24C();
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    return 0;
}
