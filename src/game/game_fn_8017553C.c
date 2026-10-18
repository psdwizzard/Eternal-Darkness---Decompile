extern int fn_80201B44();
extern void *fn_80201814();
extern int fn_80201EB8();
extern int fn_80200F3C(int, int);
extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];
extern const double lbl_806506A8;

int fn_8017553C(void* state)
{
    int first;
    int second;
    int result;

    first = fn_80201B44();
    fn_80201814();
    second = fn_80201EB8();
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    result = fn_80200F3C(first, second);
    lua_pushnumber(state, result);
    return 1;
}
