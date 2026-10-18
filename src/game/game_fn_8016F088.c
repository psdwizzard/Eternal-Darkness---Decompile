extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80128C28(void*, void*, unsigned int);
extern void fn_8016FFA8(void);
extern const char lbl_8024FF00[];

int fn_8016F088(void* state)
{
    void* queue;
    int value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    queue = lua_touserdata(state, 1);
    value = (int)lua_tonumber(state, 2);
    fn_80128C28(queue, fn_8016FFA8, value);
    return 0;
}
