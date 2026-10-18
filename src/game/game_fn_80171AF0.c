extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801ACACC(int, int, int, int);
extern const char lbl_8024FF00[];

int fn_80171AF0(void* state)
{
    int arg1;
    int arg2;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    arg1 = (int)lua_tonumber(state, 1);
    arg2 = (int)lua_tonumber(state, 2);
    fn_801ACACC(arg1, arg2, 0, (int)lua_tonumber(state, 3));
    return 0;
}
