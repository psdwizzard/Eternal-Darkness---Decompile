extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern void *fn_80201814();
extern void fn_80201D2C(void*, int);
extern void fn_80201D14(void*, int);
extern const char lbl_8024FF00[];

int fn_8016C96C(void* state)
{
    void* object;
    int second;
    int first;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }
    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    object = fn_80201814(first);
    if (object != 0) {
        fn_80201D2C(object, second);
        fn_80201D14(object, 1);
    }
    return 0;
}
