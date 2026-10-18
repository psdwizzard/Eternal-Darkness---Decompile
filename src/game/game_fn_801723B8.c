extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801B2380(int);
extern void fn_801B2348(int);
extern const char lbl_8024FF00[];
extern const char lbl_80250404[];

int fn_801723B8(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    if (value == 1) {
        fn_801B2380(0);
    } else if (value == 0) {
        fn_801B2348(0);
    } else {
        luaO_verror(state, lbl_80250404, value);
    }
    return 0;
}
