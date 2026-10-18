extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned long long fn_8020123C();
extern const char lbl_8024FF00[];

int fn_8016D7AC(void* state)
{
    int values[4];
    int x;
    int y;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }
    x = (int)lua_tonumber(state, 1);
    y = (int)lua_tonumber(state, 2);
    values[0] = (int)lua_tonumber(state, 3);
    values[1] = (int)lua_tonumber(state, 4);
    if (x != 0) {
        fn_8020123C(y, 0, x, values);
    }
    return 0;
}
