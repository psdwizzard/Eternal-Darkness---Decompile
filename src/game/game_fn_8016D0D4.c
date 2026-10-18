extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern int lbl_8064CB54;

int fn_8016D0D4(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }
    lbl_8064CB54 ^= 1;
    return 0;
}
