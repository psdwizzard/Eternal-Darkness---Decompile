extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_801A5CE0(void);
extern int fn_801A5D04(void);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_8016FEF8(void* state)
{
    int value;

    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    value = 0;
    if (fn_801A5CE0() != 0 || fn_801A5D04() != 0) {
        value = 1;
    }
    lua_pushnumber(state, value);
    return 1;
}
