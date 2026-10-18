extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80046CE4(int);
extern void fn_80046DB4(int);
extern const char lbl_8024FF00[];
extern const double lbl_806506D0;

int fn_801749A8(void* state)
{
    int value;
    double second_value;

    switch (lua_gettop(state)) {
    case 2:
        value = lua_tonumber(state, 1);
        second_value = lua_tonumber(state, 2);
        if (second_value == lbl_806506D0) {
            fn_80046CE4(value);
        } else {
            fn_80046DB4(value);
        }
        break;
    case 1:
        fn_80046CE4(lua_tonumber(state, 1));
        break;
    default:
        if (lua_gettop(state) != 1) {
            luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
            return 0;
        }
        break;
    }
    return 0;
}
