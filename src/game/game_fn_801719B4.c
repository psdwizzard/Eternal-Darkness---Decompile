extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_800471F8(void);
extern void fn_801AD734(int);
extern void fn_801AD770(unsigned short, int);
extern void lua_pushnumber(void*, double);
extern const char lbl_8024FF00[];

int fn_801719B4(void* state)
{
    int result;
    int arg2;
    int arg4;
    int arg1;
    int arg3;
    int arg5;

    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }

    arg1 = (int)lua_tonumber(state, 1);
    arg2 = (int)lua_tonumber(state, 2);
    arg3 = (int)lua_tonumber(state, 3);
    arg4 = (int)lua_tonumber(state, 4);
    arg5 = (int)lua_tonumber(state, 5);
    result = fn_800471F8();
    if (result != 0) {
        if (arg1 != 0) {
            fn_801AD734(arg1);
        }
        fn_801AD770((unsigned short)arg2, arg5);
        fn_801AD734(arg3);
        fn_801AD770((unsigned short)arg4, arg5);
    }

    lua_pushnumber(state, result);
    return 1;
}
