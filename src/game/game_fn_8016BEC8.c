extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801A9DCC(int, int, int);
extern const char lbl_8024FF00[];

int fn_8016BEC8(void* state)
{
    int amount;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    amount = (int)lua_tonumber(state, 1);
    fn_801A9DCC(0, amount == 1 ? 25 : 100, 10);
    return 0;
}
