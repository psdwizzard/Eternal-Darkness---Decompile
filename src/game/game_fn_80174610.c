extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void* fn_80156948(int);
extern void fn_80153104(void*);
extern const char lbl_8024FF00[];

int fn_80174610(void* state)
{
    void* object;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    object = fn_80156948(fn_800F5C54(lua_tonumber(state, 1)));
    if (object != 0) {
        fn_80153104(object);
    }
    return 0;
}
