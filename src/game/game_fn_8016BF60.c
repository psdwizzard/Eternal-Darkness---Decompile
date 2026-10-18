extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801B0B30(int);
extern int fn_801AF924(void);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_8016BF60(void* state)
{
    int result;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    fn_801B0B30((int)lua_tonumber(state, 1));
    result = fn_801AF924();
    lua_pushnumber(state, result);
    return 1;
}
