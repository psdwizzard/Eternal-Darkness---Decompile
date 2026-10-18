extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void fn_801F74C8(int, int, int);
extern const char lbl_8024FF00[];

int fn_80170438(void* state)
{
    int first;
    int second;
    int third;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (int)lua_tonumber(state, 3);
    fn_801F74C8(first, second, third);
    return 0;
}
