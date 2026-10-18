typedef signed short s16;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8016B0B4(s16, int);
extern int lbl_8064D1BC;
extern const char lbl_80250164[];

int fn_80170B5C(void* state)
{
    s16 first = lbl_8064D1BC;
    int second;

    switch (lua_gettop(state)) {
    case 2:
        first = lua_tonumber(state, 2);
    case 1:
        second = lua_tonumber(state, 1);
        break;
    default:
        luaO_verror(state, lbl_80250164, lua_gettop(state));
        return 0;
    }

    fn_8016B0B4(first, second);
    return 0;
}
