extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int lbl_8064D1C4;
extern const char lbl_8024FF00[];

int fn_80170C84(void* state)
{
    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    lbl_8064D1C4 = lua_tonumber(state, 1);
    return 0;
}
