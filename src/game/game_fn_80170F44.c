extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern void* fn_80158ABC(int, int, void*);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];
extern const char lbl_8025009C[];

int fn_80170F44(void* state)
{
    int handle;
    int index;
    void* result;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    handle = fn_800F5C54(lua_tonumber(state, 1));
    index = fn_8015C4A4(handle, 2);
    if (index != -1) {
        result = fn_80158ABC(index, 2, 0);
        lua_pushusertag(state, result, 0);
    } else {
        luaO_verror(state, lbl_8025009C, handle);
        lua_pushusertag(state, 0, 0);
    }
    return 1;
}
