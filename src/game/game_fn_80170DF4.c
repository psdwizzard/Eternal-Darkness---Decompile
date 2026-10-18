extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_801E79FC(void*, int);
extern void lua_pushnumber(void*, double);
extern void* lbl_8064C4E0;
extern const char lbl_8024FF00[];

int fn_80170DF4(void* state)
{
    int handle;
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    handle = fn_800F5C54(lua_tonumber(state, 1));
    value = fn_801E79FC(lbl_8064C4E0, handle);
    lua_pushnumber(state, value);
    return 1;
}
