typedef signed short s16;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8016ADF0(s16, int, int);
extern int lbl_8064D1BC;
extern const char lbl_80250164[];

int fn_80170980(void* state)
{
    int value;
    s16 id = lbl_8064D1BC;

    switch (lua_gettop(state)) {
    case 2:
        id = lua_tonumber(state, 2);
    case 1:
        value = (int)lua_tonumber(state, 1);
        break;
    default:
        luaO_verror(state, lbl_80250164, lua_gettop(state));
        return 0;
    }

    fn_8016ADF0(id, value, -1);
    return 0;
}
