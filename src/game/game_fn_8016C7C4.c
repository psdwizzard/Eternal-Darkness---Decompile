extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void fn_8015C8A4(int, int);
extern const char lbl_8024FF00[];

int fn_8016C7C4(void* state)
{
    switch (lua_gettop(state)) {
    case 2: {
        int value = (int)lua_tonumber(state, 1);
        fn_8015C8A4(fn_800F5C54(lua_tonumber(state, 2)), value);
        break;
    }
    default:
        if (lua_gettop(state) != 1) {
            luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
            return 0;
        }
        fn_8015C8A4(1, (int)lua_tonumber(state, 1));
        break;
    }
    return 0;
}
