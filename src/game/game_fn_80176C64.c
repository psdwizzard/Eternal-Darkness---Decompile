extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801593B4(int);
extern void fn_801593FC(int);
extern const char lbl_8024FF00[];

int fn_80176C64(void* state)
{
    int id;
    int enabled;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    id = (int)lua_tonumber(state, 1);
    enabled = (int)lua_tonumber(state, 2);
    if (enabled != 0) {
        fn_801593B4(id);
    } else {
        fn_801593FC(id);
    }
    return 0;
}
