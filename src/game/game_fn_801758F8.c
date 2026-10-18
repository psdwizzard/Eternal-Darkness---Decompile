extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8011E26C(int);
extern const char lbl_8024FF00[];

int fn_801758F8(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    fn_8011E26C(1);
    return 0;
}
