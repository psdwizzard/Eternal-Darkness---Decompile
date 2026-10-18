extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int rand(void);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_8017718C(void* state)
{
    int divisor;
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    divisor = (int)lua_tonumber(state, 1);
    value = (int)rand() % divisor;
    lua_pushnumber(state, (double)value);
    return 1;
}
