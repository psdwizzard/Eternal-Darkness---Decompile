extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801287C4(void*, void*, unsigned int, unsigned int);
extern void fn_8016FFA8(void);
extern const char lbl_8024FF00[];

int fn_8016EFC4(void* state)
{
    void* queue;
    int first;
    int second;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    queue = lua_touserdata(state, 1);
    first = (int)lua_tonumber(state, 2);
    second = (int)lua_tonumber(state, 3);
    fn_801287C4(queue, fn_8016FFA8, first, second);
    return 0;
}
