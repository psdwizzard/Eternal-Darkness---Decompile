extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern int fn_80201B64(void*);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_8016D1F8(void* state)
{
    int result = -1;
    void* object;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }
    object = fn_80201814((int)lua_tonumber(state, 1));
    if (object != 0) {
        result = fn_80201B64(object);
    }
    lua_pushnumber(state, (double)result);
    return 1;
}
