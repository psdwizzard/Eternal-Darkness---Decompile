extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern const char lbl_8024FF00[];
extern float lbl_8063D400[];

int fn_8017038C(void* state)
{
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    value = (int)lua_tonumber(state, 1);
    lbl_8063D400[2] -= value;
    return 0;
}
