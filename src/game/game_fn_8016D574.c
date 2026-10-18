extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8020104C(int, void*, void*, int, float);
extern const char lbl_8024FF00[];

int fn_8016D574(void* state)
{
    int x;
    int y;
    float z;
    int flags;

    lua_gettop(state);
    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }
    lua_tonumber(state, 1);
    x = (int)lua_tonumber(state, 2);
    y = (int)lua_tonumber(state, 3);
    z = (float)lua_tonumber(state, 4);
    flags = (int)lua_tonumber(state, 5);
    if (x != 0) {
        fn_8020104C(y, 0, (void*)x, flags, z);
    }
    return 0;
}
