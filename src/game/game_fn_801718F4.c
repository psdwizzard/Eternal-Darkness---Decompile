extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_80052310(int, void*);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_801718F4(void* state)
{
    int value;
    unsigned int result;
    void* text;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    text = lua_touserdata(state, 2);
    result = fn_80052310(value, text);
    lua_pushnumber(state, result);
    return 1;
}
