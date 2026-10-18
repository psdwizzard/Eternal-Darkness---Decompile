extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B94();
extern int fn_80201C48(void);
extern const char lbl_8024FF00[];

int fn_8016BD0C(void* state)
{
    int result = -1;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    if (fn_80201814((int)lua_tonumber(state, 1)) != 0 && fn_80201B94() != 0) {
        result = fn_80201C48();
    }
    lua_pushnumber(state, result);
    return 1;
}
