extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801AD6F4(int);
extern const char lbl_8024FF00[];
extern const char lbl_80250358[];

int fn_80172150(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    if (value != 0 && value != 1) {
        luaO_verror(state, lbl_80250358, value);
    }
    fn_801AD6F4(value);
    return 0;
}
