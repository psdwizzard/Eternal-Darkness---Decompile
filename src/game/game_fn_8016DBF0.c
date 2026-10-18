extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801F640C(void*, int, int);
extern const char lbl_8024FF00[];

int fn_8016DBF0(void* state)
{
    int first;
    void* object;
    int second;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    object = (void *)fn_800F5C54(lua_tonumber(state, 1));
    first = (int)lua_tonumber(state, 2);
    second = (int)lua_tonumber(state, 3);
    fn_801F640C(object, first, second);
    return 1;
}
